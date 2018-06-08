project(Generic-IO)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

# configure a header file to pass some of the CMake settings
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(NumPy  REQUIRED)
FIND_PACKAGE( Boost 1.40 COMPONENTS program_options unit_test_framework REQUIRED )




set(genericIO_MAJOR_VERSION 0)
set(genericIO_MINOR_VERSION 4)
set(genericIO_VERSION_STRING
  ${genericIO_MAJOR_VERSION}.${genericIO_MINOR_VERSION})




set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fpic")
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

enable_language(C CXX)



FIND_PACKAGE( Boost 1.40 COMPONENTS program_options unit_test_framework REQUIRED )


option(INSTSLL_SEPLIB "Install with SEPLIB" OFF)


include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

FIND_PACKAGE(sepVector)
if(sepVector_FOUND)
  message("Found sepVector")
  include_directories(${sepVector_DIRNAME_include})
  set(GENERIC_EXPORT_LIBS "sepVector;${GENERIC_EXPORT_LIBS}")  
else(sepVector_FOUND)
   message("Unable to find sepVector")

    # we have a submodule setup for foo, assume it is under external/foo
    # now we need to clone this submodule
    execute_process(COMMAND git submodule update --init --recursive  -- external/sepVector
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    add_subdirectory(external/sepVector)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/external/sepVector/lib)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/external/sepVector/external/hypercube/lib)

endif(sepVector_FOUND)




FIND_PACKAGE(ZFP)
if(ZFP_FOUND)
  message("Found ZFP")
  INCLUDE_DIRECTORIES(${ZFP_INCLUDE_DIR})
else(ZFP_FOUND)

ExternalProject_Add (
       ZFP_INSTALL
       CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
      GIT_REPOSITORY "https://github.com/LLNL/zfp"
            INSTALL_DIR  ${CMAKE_INSTALL_PREFIX})

   set(ZFP_INCLUDE_DIR ${CMAKE_INSTALL_PREFIX}/include)
   if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
     set(ZFP_LIBRARIES ${CMAKE_INSTALL_PREFIX}/lib/${CMAKE_SHARED_LIBRARY_PREFIX}zfp${CMAKE_SHARED_LIBRARY_SUFFIX})   
   else()
     set(ZFP_LIBRARIES ${CMAKE_INSTALL_PREFIX}/lib64/${CMAKE_SHARED_LIBRARY_PREFIX}zfp${CMAKE_SHARED_LIBRARY_SUFFIX})
   endif()


endif(ZFP_FOUND)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")



find_path(RSFINCDIR rsf.h ${RSF_DIR}/include )



MESSAGE("Installing with SEP VECTOR")
  set(USE_SEPVECTOR true)
  include_directories(${sepVector_DIRNAME_include})
  set(GENERIC_EXPORT_LIBS "sepVector;${GENERIC_EXPORT_LIBS}")
  if(DEFINED GENERIC_EXPORT_INC_DIRS)
    set(GENERIC_EXPORT_INC_DIRS "${GENERIC_EXPORT_INC_DIRS};${sepVector_DIRNAME_include}")
    set(GENERIC_EXPORT_LIB_DIRS "${GENERIC_EXPORT_LIB_DIRS};${sepVector_DIRNAME_lib}")
   else()
     set(GENERIC_EXPORT_INC_DIRS "${sepVector_DIRNAME_include}")
     set(GENERIC_EXPORT_LIB_DIRS "${sepVector_DIRNAME_lib}")
   endif()


if (RSFINCDIR)
  MESSAGE("INSTALLING WITH RSF")
  set(USE_RSF true)
  STRING(REGEX REPLACE "include\$" "lib" luse "${RSFINCDIR}")
  set(GENERIC_EXPORT_LIBS "${GENERIC_EXPORT_LIBS};rsf")
  if(DEFINED GENERIC_EXPORT_INC_DIRS)
    set(GENERIC_EXPORT_INC_DIRS "${GENERIC_EXPORT_INC_DIRS};${RSFINCDIR}")
    set(GENERIC_EXPORT_LIB_DIRS "${GENERIC_EXPORT_LIB_DIRS};${luse}")
   else()
    set(GENERIC_EXPORT_INC_DIRS "${RSFINCDIR}")
    set(GENERIC_EXPORT_LIB_DIRS "${luse}")
   endif()
else()
  MESSAGE("NOT INSTALLING WITH RSF")
endif()





if (SEPlib_FOUND)
  MESSAGE("INSTALLING WITH SEPlib")
  set(USE_SEP true)
  set(GENERIC_EXPORT_LIBS "${GENERIC_EXPORT_LIBS};sep3d;sep")
  if(DEFINED GENERIC_EXPORT_INC_DIRS)
    set(GENERIC_EXPORT_INC_DIRS "${GENERIC_EXPORT_INC_DIRS};${SEPlib_DIRNAME_include}")
    set(GENERIC_EXPORT_LIB_DIRS "${GENERIC_EXPORT_LIB_DIRS};${SEPlib_DIRNAME_lib}")
   else()
     set(GENERIC_EXPORT_INC_DIRS "${SEPlib_DIRNAME_include}")
     set(GENERIC_EXPORT_LIB_DIRS "${SEPlib_DIRNAME_lib}")
   endif()
else()
  MESSAGE("NOT INSTALLING WITH SEPlib")
endif()

  set(GENERIC_EXPORT_LIBS "${GENERIC_EXPORT_LIBS};hypercube ")
  if(DEFINED GENERIC_EXPORT_INC_DIRS)
  MESSAGE("HYPERCUBE DIRNAME "${GENERIC_EXPORT_LIBS})
    set(GENERIC_EXPORT_INC_DIRS "${GENERIC_EXPORT_INC_DIRS};${hypercube_DIRNAME_include}")
    set(GENERIC_EXPORT_LIB_DIRS "${GENERIC_EXPORT_LIB_DIRS};${hpercube_DIRNAME_lib}")
   else()
     set(GENERIC_EXPORT_INC_DIRS "${hypercube_DIRNAME_include}")
     set(GENERIC_EXPORT_LIB_DIRS "${hpercube_DIRNAME_lib}")
   endif()


string(STRIP "${GENERIC_EXPORT_LIBS}" GENERIC_EXPORT_LIBS)
if(USE_SEP)
  set(DEFAULTIO "SEP")
elseif(USE_RSF)
    set(DEFAULTIO "RSF")
else(USE_SEP)
    set(DEFAULTIO "JSON")
endif(USE_SEP)
include_directories(${PROJECT_BINARY_DIR})

configure_file (
  "${PROJECT_SOURCE_DIR}/ioConfig.h.in"
  "${PROJECT_BINARY_DIR}/ioConfig.h"
  )
 SET(genericIO_DIRNAME_lib     "lib")
 SET(genericIO_DIRNAME_include "include")
  INCLUDE(CMakePackageConfigHelpers)

  CONFIGURE_PACKAGE_CONFIG_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/genericIOConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/genericIOConfig.cmake"
  INSTALL_DESTINATION
    ${genericIO_DIRNAME_lib}
  PATH_VARS
    genericIO_DIRNAME_include
  )
  
  INSTALL(
  FILES
    ${CMAKE_CURRENT_BINARY_DIR}/genericIOConfig.cmake
  DESTINATION
    lib
  )


  INSTALL(
  EXPORT
    genericIOExports
  DESTINATION
    ${genericIO_DIRNAME_lib}
  )
  
add_subdirectory(cpp)


option(BUILD_FORTRAN "Build fortran support" OFF)

if(BUILD_FORTRAN)
  enable_language(FORTRAN)
  add_subdirectory(fortran)
endif(BUILD_FORTRAN)
add_subdirectory(python)
add_subdirectory(util)
add_subdirectory(env-modules)

install(FILES ${PROJECT_BINARY_DIR}/ioConfig.h  DESTINATION include)


include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${genericIO_MAJOR_VERSION}")
set(CPACK_PACKAGE_VERSION_MINOR "${genericIO_MINOR_VERSION}")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_NAME "sepVector")
set(CPACK_PACKAGE_CONTACT "Robert Clapp")
include(CPack)

