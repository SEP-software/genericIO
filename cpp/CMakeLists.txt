cmake_minimum_required(VERSION 2.8)
project(Generic-cpp)

set(SOURCES  basicIO.cpp  genericFile.cpp  )
set(SOURCES ${SOURCES} jsonParamObj.cpp jsonGenericFile.cpp genericIO.cpp)
set (SOURCES ${SOURCES} jsonGenericIO.cpp ioModes.cpp segyIO.cpp buffersIO.cpp buffersRegFile.cpp)
set(INCLUDES  genericIO.h jsonGenericFile.h	jsonParamObj.h basicIO.h )
set(INCLUDES ${INCLUDES} jsonGenericIO.h	paramObj.h genericFile.h ioModes.h segyIO.h
	buffersIO.h buffersRegFile.h)

if(USE_SEP)
MESSAGE("ADDING SEP STUFF")
include_directories(${SEPlib_DIRNAME_include})
  set(SOURCES  ${SOURCES} sepIO.cpp  sep3dFile.cpp sep_reg_file.cpp  sep_params.cpp )
  set(INCLUDES ${INCLUDES} sep_params.h sepIO.h sep3dFile.h sep_reg_file.h)
endif(USE_SEP)

if(USE_RSF)
include_directories(${RSFINCDIR})
  set(SOURCES  ${SOURCES} rsfIO.cpp	rsfParams.cpp  rsfRegFile.cpp)
  set(INCLUDES ${INCLUDES}  rsfIO.h rsfParams.h rsfRegFiles.h ) 
endif(USE_RSF)
   add_library(genericCpp ${SOURCES} ${INCLUDES})
target_link_libraries(genericCpp sepVector jsonCpp)

if(USE_SEP)
target_link_libraries(genericCpp sep3d sep)
endif(USE_SEP)

install(FILES ${INCLUDES} DESTINATION include)
install(TARGETS genericCpp DESTINATION lib EXPORT genericIOExports)
