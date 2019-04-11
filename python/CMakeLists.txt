project(Generic-IO)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

find_package(NumPy REQUIRED)

# This is a CMake example for Python
find_package(pybind11)
if(pybind11_FOUND)
  find_package(PythonLibs)
  find_package(PythonInterp 3 REQUIRED)

  pybind11_add_module(pyGenericIO MODULE pyIO.cpp)
  target_include_directories(
    pyGenericIO
    PUBLIC ${PYTHON_INCLUDE_DIR}
           ${pybind11_INCLUDE_DIR}
           ${PYTHON_INCLUDE_PATH}
           $<INSTALL_INTERFACE:include>
           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}../src>)

  target_link_libraries(pyGenericIO PRIVATE genericCpp)
  install(TARGETS pyGenericIO DESTINATION lib/python EXPORT genericIOTargets)
  install(FILES genericIO.py DESTINATION lib/python)
else(pybind11_FOUND)
  message("Did not find pybid11")
endif(pybind11_FOUND)
