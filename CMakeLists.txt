project(Generic-IO)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

# configure a header file to pass some of the CMake settings





 
# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pg")

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
find_path(RSFINCDIR rsf.h /opt/RSF/1.7/include /opt/RSF/include)

set(CMAKE_Fortran_MODULE_DIRECTORY  ${CMAKE_INSTALL_PREFIX}/include)

if (RSFINCDIR)
  set(USE_RSF true)
else()
endif()

#!if (SEPINCDIR AND LIBSEP AND LIBSEP3D)
if (SEPINCDIR)
  set(USE_SEP true)
else()
endif()

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
add_subdirectory(cpp)
add_subdirectory(fortran)
install(FILES ${PROJECT_BINARY_DIR}/ioConfig.h  DESTINATION include)
