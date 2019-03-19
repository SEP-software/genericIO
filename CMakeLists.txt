cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(genericIO LANGUAGES CXX)

if(NOT SUBPACKAGE)
  option(BUILD_PYTHON "Build python interfaces" ON)
  option(INSTALL_CMAKE_ENV "Install cmake build environment" ON)
  option(BUILD_UTIL "Build utilities" ON)
else(NOT SUBPACKAGE)
  option(BUILD_UTIL "Build utilities" OFF)
endif(NOT SUBPACKAGE)
  option(BUILD_GCP "Build GCP" OFF)
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

set(genericIO_VERSION ${genericIO_VERSION_STRING})
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
    include_directories(${CMAKE_CURRENT_BINARY_DIR}/external/buffers)

  include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/external/sepVector/external/hypercube/lib)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/external/buffers)
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


find_path(RSFINCDIR rsf.h ${RSF_DIR}/include)

set(USE_SEPVECTOR true)
include_directories(${sepVector_DIRNAME_include})
set(GENERIC_EXPORT_LIBS "sepVector;${GENERIC_EXPORT_LIBS}")
if(DEFINED GENERIC_EXPORT_INC_DIRS)
  set(GENERIC_EXPORT_INC_DIRS
      "${GENERIC_EXPORT_INC_DIRS};${sepVector_DIRNAME_include}")
  set(GENERIC_EXPORT_LIB_DIRS
      "${GENERIC_EXPORT_LIB_DIRS};${sepVector_DIRNAME_lib}" )
else()
  set(GENERIC_EXPORT_INC_DIRS "${sepVector_DIRNAME_include}")
  set(GENERIC_EXPORT_LIB_DIRS "${sepVector_DIRNAME_lib}" )
endif()


find_package(SEPlib)



if(SEPlib_FOUND)
  message("INSTALLING WITH SEPlib")
  set(USE_SEP true)
  list(APPEND GENERIC_EXPORT_LIBS "sep3d")
  list(APPEND GENERIC_EXPORT_LIBS "sep")
  link_directories(${SEPlib_LIBRARY_DIRS})
  include_directories(${SEPlib_INCLUDE_DIRS})
  list(APPEND GENERIC_EXPORT_INC_DIRS ${SEPlib_INCLUDE_DIRS} )
  list(APPEND GENERIC_EXPORT_LIB_DIRS ${SEPlib_LIBRARY_DIRS} )
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


configure_file("${PROJECT_SOURCE_DIR}/ioConfig.h.in"
               "${PROJECT_BINARY_DIR}/ioConfig.h")
set(genericIO_DIRNAME_lib "lib")
set(genericIO_DIRNAME_include "include")
set(genericIO_DIRNAME_cmake "cmake")
# cmake file
configure_file (genericIOConfig.cmake.in genericIOConfig.cmake @ONLY)
configure_file (genericIOConfigVersion.cmake.in genericIOConfigVersion.cmake @ONLY)


install (FILES
          ${CMAKE_CURRENT_BINARY_DIR}/genericIOConfig.cmake
          ${CMAKE_CURRENT_BINARY_DIR}/genericIOConfigVersion.cmake
    DESTINATION lib/cmake
    COMPONENT Development)




if(BUILD_GCP)
  message("SEE GCP")
  set(USE_GCP true)
  find_package(storage_client 0.3.0 REQUIRED )

 if(GOOGLE_STORAGE_ROOT)
    include_directories(${GOOGLE_STORAGE_ROOT}/include)
 else(GOOGLE_STORAGE_ROOT)
    MESSAGE(FATAL_ERROR "Must specitfy GOOGLE_STORAGE_ROOT")
 endif(GOOGLE_STORAGE_ROOT)
else(BUILD_GCP)
  message("Don't see GCP")
endif(BUILD_GCP)


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

