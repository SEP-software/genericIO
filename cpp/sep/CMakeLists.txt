cmake_minimum_required(VERSION 2.8)
project(Generic-sep)

include_directories(${SEPINCDIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../base)

add_library(genCppSep 	sep_reg_file.cpp)
