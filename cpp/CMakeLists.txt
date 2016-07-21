cmake_minimum_required(VERSION 2.8)
project(Generic-IO)

add_subdirectory(base)


if (USE_SEP)
   add_subdirectory(sep)
endif (USE_SEP)
