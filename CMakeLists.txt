project(Generic-IO)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

enable_language(Fortran C CXX)

find_path(SEPINCDIR seplib.h /usr/local/SEP/include /usr/local/SEP/SEP8.0/include /opt/SEP/include /opt/SEP/SEP8.0/include)
find_library(LIBSEP sep /usr/local/SEP/lib /usr/local/SEP/SEP8.0/lib /opt/SEP/lib /opt/SEP/SEP8.0/lib)
find_library(LIBSEP3D sep3d /usr/local/SEP/lib /usr/local/SEP/SEP8.0/lib /opt/SEP/lib /opt/SEP/SEP8.0/lib)

#!if (SEPINCDIR AND LIBSEP AND LIBSEP3D)
if (SEPINCDIR)
  set(USE_SEP true)
  set(IOTYPE SEP)
else()
endif()

configure_file (
  "${PROJECT_SOURCE_DIR}/genericIO.h.in"
  "${PROJECT_BINARY_DIR}/genericIO.h"
 )

add_subdirectory(cpp)
add_subdirectory(fortran)
