cmake_minimum_required(VERSION 2.8)
project(Generic-fortran Fortran)

add_library(genForBase axis.f90 hypercube.f90  param_func.f90 genericFile.f90)

#set(CMAKE_Fortran_MODULE_DIRECTORY $(CMAKE_BINARY_DIR}/mod_files)

#sinstall(DIRECTORY ${CMAKE_Fortran_MODULE_DIRECTORY}/ DESTINATION include)