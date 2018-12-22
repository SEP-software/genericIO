cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(genericIO LANGUAGES CXX)

if(NOT SUBPACKAGE)
  option(BUILD_PYTHON "Build python interfaces" ON)
  option(INSTALL_CMAKE_ENV "Install cmake build environment" ON)
  option(BUILD_UTIL "Build utilities" ON)
else(NOT SUBPACKAGE)
  option(BUILD_UTIL "Build utilities" OFF)
endif(NOT SUBPACKAGE)
set(SUBPACKAGE true)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_POSITION_INDEPENDENT_CODE True)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(TBB REQUIRED)

set(genericIO_MAJOR_VERSION 0)
set(genericIO_MINOR_VERSION 4)
set(genericIO_VERSION_STRING
    ${genericIO_MAJOR_VERSION}.${genericIO_MINOR_VERSION})

include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

if(NOT TARGET sepVector)
  include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/external/sepVector/external/hypercube/lib)
  execute_process(COMMAND git submodule update --init --recursive --
                          external/sepVector
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/sepVector)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/sepVector/lib)
  include_directories(${CMAKE_CURRENT_BINARY_DIR}/external/sepVector)
  include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/external/sepVector/external/hypercube/lib)

  include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/external/buffers/external/json)
  include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}/external/buffers/ZFP_INSTALL-prefix/src/ZFP_INSTALL/include
    )
  include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/external/buffers/external/json)

  execute_process(COMMAND git submodule update --init --recursive --
                          external/buffers
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
  add_subdirectory(external/buffers)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/buffers/lib)
else(NOT TARGET sepVector)
  find_package(json REQUIRED)
  find_package(buffers REQUIRED)
  find_package(hypercube REQUIRED)
endif(NOT TARGET sepVector)

include_directories("${PROJECT_BINARY_DIR}")

find_path(RSFINCDIR rsf.h ${RSF_DIR}/include)

set(USE_SEPVECTOR true)
include_directories(${sepVector_DIRNAME_include})
set(GENERIC_EXPORT_LIBS "sepVector;${GENERIC_EXPORT_LIBS}")
if(DEFINED GENERIC_EXPORT_INC_DIRS)
  set(GENERIC_EXPORT_INC_DIRS
      "${GENERIC_EXPORT_INC_DIRS};${sepVector_DIRNAME_include}")
  set(GENERIC_EXPORT_LIB_DIRS
      "${GENERIC_EXPORT_LIB_DIRS};${sepVector_DIRNAME_lib}")
else()
  set(GENERIC_EXPORT_INC_DIRS "${sepVector_DIRNAME_include}")
  set(GENERIC_EXPORT_LIB_DIRS "${sepVector_DIRNAME_lib}")
endif()

if(RSFINCDIR)
  message("INSTALLING WITH RSF")
  set(USE_RSF true)
  string(REGEX
         REPLACE "include\$"
                 "lib"
                 luse
                 "${RSFINCDIR}")
  set(GENERIC_EXPORT_LIBS "${GENERIC_EXPORT_LIBS};rsf")
  if(DEFINED GENERIC_EXPORT_INC_DIRS)
    set(GENERIC_EXPORT_INC_DIRS "${GENERIC_EXPORT_INC_DIRS};${RSFINCDIR}")
    set(GENERIC_EXPORT_LIB_DIRS "${GENERIC_EXPORT_LIB_DIRS};${luse}")
  else()
    set(GENERIC_EXPORT_INC_DIRS "${RSFINCDIR}")
    set(GENERIC_EXPORT_LIB_DIRS "${luse}")
  endif()
else()
  message("NOT INSTALLING WITH RSF")
endif()

find_package(SEPlib)



if(SEPlib_FOUND)
  message("INSTALLING WITH SEPlib")
  set(USE_SEP true)
  list(APPEND GENERIC_EXPORT_LIBS "sep3d")
  list(APPEND GENERIC_EXPORT_LIBS "sep")

  MESSAGE("HERE WO GO "${SEPlib_INCLUDE_DIRS})
  list(APPEND GENERIC_EXPORT_INC_DIRS ${SEPlib_INCLUDE_DIRS})
  list(APPEND GENERIC_EXPORT_LIB_DIRS ${SEPlib_LIBRARY_DIRS})
else()
  message("NOT INSTALLING WITH SEPlib")
endif()



if(USE_SEP)
  set(DEFAULTIO "SEP")
elseif(USE_RSF)
  set(DEFAULTIO "RSF")
else(USE_SEP)
  set(DEFAULTIO "JSON")
endif(USE_SEP)
include_directories(${PROJECT_BINARY_DIR})


MESSAGE("HERE WE GO " ${GENERIC_EXPORT_INC_DIRS})
configure_file("${PROJECT_SOURCE_DIR}/ioConfig.h.in"
               "${PROJECT_BINARY_DIR}/ioConfig.h")
set(genericIO_DIRNAME_lib "lib")
set(genericIO_DIRNAME_include "include")
set(genericIO_DIRNAME_cmake "cmake")
include(CMakePackageConfigHelpers)

if(NOT SUPPORT_LIBRARIES_BUILD)
  configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/genericIOConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/genericIOConfig.cmake"
    INSTALL_DESTINATION
    ${genericIO_DIRNAME_lib}
    PATH_VARS
    genericIO_DIRNAME_include)

  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/genericIOConfig.cmake
          DESTINATION lib/cmake)

  if(NOT INSTALL_CMAKE_ENV)
    install(EXPORT genericIOExports DESTINATION ${genericIO_DIRNAME_cmake})
  endif(NOT INSTALL_CMAKE_ENV)
endif(NOT SUPPORT_LIBRARIES_BUILD)

add_subdirectory(cpp)

if(BUILD_PYTHON)
  add_subdirectory(python)
endif(BUILD_PYTHON)

if(BUILD_UTIL)
  add_subdirectory(util)
endif(BUILD_UTIL)

if(NOT SUPPORT_LIBRARIES_BUILD)
  install(FILES ${PROJECT_BINARY_DIR}/ioConfig.h DESTINATION include)
  add_subdirectory(env-modules)
endif(NOT SUPPORT_LIBRARIES_BUILD)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${genericIO_MAJOR_VERSION}")
set(CPACK_PACKAGE_VERSION_MINOR "${genericIO_MINOR_VERSION}")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_NAME "genericIO")
set(CPACK_PACKAGE_CONTACT "Robert Clapp")
include(CPack)
