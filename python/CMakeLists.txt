project(Generic-IO)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)



# This is a CMake example for Python
find_package(pybind11)  
if (pybind11_FOUND)

include_directories(${PYTHON_INCLUDE_DIR})
include_directories(${pybind11_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../cpp")


MESSAGE("found pybind11 building python interface")
FIND_PACKAGE(PythonLibs)
INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../cpp)
INCLUDE_DIRECTORIES(${GENERIC_EXPORT_INC_DIRS})


set(JUNK genericCpp hypercube ${GENERIC_EXPORT_LIBS})

MESSAGE(${JUNK})

pybind11_add_module(pyGenericIO MODULE pyIO.cpp)
target_link_libraries(pyGenericIO PRIVATE  ${JUNK})


install( TARGETS pyGenericIO DESTINATION lib/python)


else(pybind11_FOUND)
MESSAGE("Did not find pybid11")
endif(pybind11_FOUND)
