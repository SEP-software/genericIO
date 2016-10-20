cmake_minimum_required(VERSION 2.8)
project(Generic-sep)

include_directories(${RSFINCDIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../base)

add_library(genCppRSF 	rsfParams.cpp  rsfRegFile.cpp rsfIO.cpp)
