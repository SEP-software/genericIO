project(Generic-IO-util)
cmake_minimum_required(VERSION 2.8)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../cpp)

FIND_PACKAGE(TBB REQUIRED)


# use, i.e. don't skip the full RPATH for the build tree
set(CMAKE_SKIP_BUILD_RPATH FALSE)

# when building, don't use the install RPATH already (but later on when
# installing)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

# add the automatically determined parts of the RPATH which point to directories
# outside the build tree to the install RPATH
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

FOREACH(lib ${GENERIC_EXPORT_LIB_DIRS})
  link_directories(${lib})
ENDFOREACH(lib)






  set(UTILSZ Compress  Decompress)
  foreach(util ${UTILSZ})
      ADD_EXECUTABLE(${util} ${util}.cc)
      TARGET_LINK_LIBRARIES(${util} genericCpp sepVector buffers hypercube tbb )
      install(TARGETS ${util} DESTINATION bin)
  endforeach(util)


install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/SEP2JSON DESTINATION bin)
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/JSONIZE DESTINATION bin)


set(PYSEARCH ${CMAKE_CURRENT_BINARY_DIR}/../lib)
set(PYSEARCH ${PYSEARCH}:${CMAKE_CURRENT_BINARY_DIR}/)
set(PYSEARCH ${PYSEARCH}:${CMAKE_CURRENT_SOURCE_DIR}/)
set(PYSEARCH ${PYSEARCH}:${CMAKE_CURRENT_SOURCE_DIR}/../python)
set(PYSEARCH ${PYSEARCH}:${CMAKE_CURRENT_SOURCE_DIR}/../external/sepVector/python)
set(PYSEARCH ${PYSEARCH}:${CMAKE_CURRENT_BINARY_DIR}/../external/sepVector/python)
set(PYSEARCH ${PYSEARCH}:${CMAKE_CURRENT_BINARY_DIR}/../external/sepVector/lib)
set(PYSEARCH ${PYSEARCH}:${CMAKE_CURRENT_SOURCE_DIR}/../external/sepVector/external/hypercube/python)
set(PYSEARCH ${PYSEARCH}:${CMAKE_CURRENT_BINARY_DIR}/../external/sepVector/external/hypercube/python)
set(PYSEARCH ${PYSEARCH}:${CMAKE_CURRENT_BINARY_DIR}/../external/sepVector/external/hypercube/lib)
set(PYSEARCH ${PYSEARCH}:${CMAKE_CURRENT_SOURCE_DIR}/../external/sepVector/external/python-solver/GenericSolver/python)

  if(BUILD_TEST)
  set(TESTS  GenDd )
FOREACH(prg ${TESTS})
  add_test(NAME TEST_${prog}
  COMMAND ${CMAKE_COMMAND} -E env
  PYTHONPATH=${PYSEARCH}
  LD_LIBRARY_PATH=${PYSEARCH}
  DATAPATH=/tmp/
  ${PYTHON_EXECUTABLE} -m test_${prg}
WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
ENDFOREACH(prg)
endif(BUILD_TEST)
message("CHECK FOUR" ${GEN_IO_TYPES})

set(SCRIPTS  GenIn GenDd GenAttr)
FOREACH(prg ${SCRIPTS})
   configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/${prg}.py"
  "${CMAKE_CURRENT_BINARY_DIR}/${prg}"
  @ONLY
  )
   install(PROGRAMS  ${CMAKE_CURRENT_BINARY_DIR}/${prg} DESTINATION bin)
ENDFOREACH(prg)

install(PROGRAMS ${progs} DESTINATION bin)