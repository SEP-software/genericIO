project(Generic-IO)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)



# This is a CMake example for Python

FIND_PACKAGE(SWIG REQUIRED)
if(SWIG_FOUND)
MESSAGE("found SWIG building python interface")
INCLUDE(${SWIG_USE_FILE})

FIND_PACKAGE(PythonLibs)
INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../cpp)
INCLUDE_DIRECTORIES(${GENERIC_EXPORT_INC_DIRS})

SET(CMAKE_SWIG_FLAGS "")

SET_SOURCE_FILES_PROPERTIES(genericIO.i PROPERTIES CPLUSPLUS ON)
SWIG_ADD_MODULE(genericFile_int   python  genericFile.i ../lib/genericFile.cpp)
SWIG_ADD_MODULE(genericIO_int   python  genericIO.i ../lib/genericIO.cpp)
SWIG_ADD_MODULE(ioModes_int   python  ioModes.i ../lib/ioModes.cpp)
#SWIG_ADD_LIBRARY(genericIO_int LANGUAGE python TYPE MODULE SOURCES genericIO.i ../cpp/genericIO.cpp)
#SWIG_ADD_LIBRARY(genericFile_int LANGUAGE python TYPE MODULE SOURCES genericFile.i ../cpp/genericFile.cpp)
#SWIG_ADD_LIBRARY(ioModes_int LANGUAGE python TYPE MODULE SOURCES ioModes.i ../cpp/ioModes.cpp)

SWIG_LINK_LIBRARIES(genericIO_int hypercube ${PYTHON_LIBRARIES})

SET_SOURCE_FILES_PROPERTIES(genericFile.i PROPERTIES CPLUSPLUS ON)



SWIG_LINK_LIBRARIES(ioModes_int genericCpp hypercube ${GENERIC_EXPORT_LIBS} ${PYTHON_LIBRARIES})

SWIG_LINK_LIBRARIES(genericFile_int hypercube  ${PYTHON_LIBRARIES})

SET_SOURCE_FILES_PROPERTIES(ioModes.i PROPERTIES CPLUSPLUS ON)


install( TARGETS _ioModes_int _genericFile_int _genericIO_int DESTINATION lib)
install( FILES ${CMAKE_CURRENT_SOURCE_DIR}/__init__.py ${CMAKE_CURRENT_BINARY_DIR}/ioModes_int.py  ${CMAKE_CURRENT_BINARY_DIR}/genericFile_int.py  ${CMAKE_CURRENT_BINARY_DIR}/genericIO_int.py DESTINATION lib/python/SEP)



else(SWIG_FOUND)
MESSAGE("Did not find SWIG, not building python interface")
endif(SWIG_FOUND)
