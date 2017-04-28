#!/bin/bash
rm -rf build
mkdir build
cd build
cmake  -DCMAKE_INSTALL_PREFIX=/opt/genericIO ..
make
make install
