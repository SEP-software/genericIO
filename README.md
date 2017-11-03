# qtcube
Pre-reqs

Make sure you have boost filesystems installed.  You need to install two small libraries before installing Born.

Install instructions



Install hypercube


git clone http://zapad.Stanford.EDU/bob/hypercube.git   /opt/hypercube/src 
mkdir /opt/hypercube/build 
 cd /opt/hypercube/build 
   cmake -DCMAKE_INSTALL_PREFIX=/opt/hypercube ../src 
   make install 


Install zfp
 mkdir -p /opt/zfp/build  &&\
  cd /opt/zfp/build  && \
 cmake -DCMAKE_INSTALL_PREFIX=/opt/zfp  ../src  && \
   make &&\
 make install


export ZFP_ROOT_DIR=/opt/zfp/build 

git clone http://zapad.Stanford.EDU/bob/genericIO.git /opt/genericIO/src 
mkdir /opt/genericIO/build
cd /opt/genericIO/build
cmake  -Dhypercube_DIR=/opt/hypercube/lib  -DCMAKE_INSTALL_PREFIX=/opt/genericIO ../src
make install 


