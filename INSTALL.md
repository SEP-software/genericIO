# Installing genericIO


GenericIO uses submodules for most of its dependencies. There are additional optional functionality
enabled by preinstalling other packages.

GenericIO works on any modern linuxOS and normally MacOS (there is currently big in the latest version of MacOS that
should be fixed soon). 


# Pre-steps on Debian:

1. Install basic tools

apt-get -y install  g++ python3-numpy git make gcc libboost-all-dev  wget pybind11-python

2. Install up to date version of cmake

cd /tmp &&  \
   wget https://github.com/Kitware/CMake/releases/download/v3.14.0-rc2/cmake-3.14.0-rc2.tar.gz
cd /tmp && \
  tar xf /opt/cmake/cmake-3.14.0-rc2.tar.gz &&\
  cd  /tmp/cmake-3.14.0-rc2 && \
 ./bootstrap &&\
 make -j 8 &&\
 make install


# Pre-steps on CentOS









# Optional packages

1. You can build the documentation if you preinstall doxygen.
2. You can build support for old SEPlib style packages by first installing IO-libs package from
  http://cees-gitlab.stanford.EDU/SEP-external/sep-iolibs.git
3. You can also build for support for GCP by preinstalling Google GCP cloud library from
  https://github.com/googleapis/google-cloud-cpp.git.  You must follow the recommended install
  almost exactly. 
   a. The pre-installed packages must be installed standard system paths. The library will fail to build correctly if you specify alternate paths.
   b. You need to specify the -DCMAKE_CXX_FLAGS='-fPIC' (on linux) when building the library. Otherwise a relocation error will occur when linking against the library.
   c. Currently GCP can not be succesfully built in a docker (at least on a mac). It will hang when compiling.
   d. You can not include the GCP library as a sub-module.  It does not correctly handle all its internal dependencies.


# Configuring genericIO

GenericIO uses cmake for configuration.  There are many options available in the build process but for the first time users. The standard options are recommended with the possible additions of:
  - -DBUILD_GCP=yes  Build with GCP support
  - -DBUILD_DOC=no   Turn on/off documentation building

  For example a standard configuration might look like

  cmake -DCMAKE_INSTALL_PREFIX=/build/SEP -DBUILD_GCP=yes -DBUILD_DOC=no -DBUILD_TESTS=yes ../src

  where src is the location of the genericIO code
