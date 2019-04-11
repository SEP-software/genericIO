cmake_minimum_required(VERSION 3.1)
project(genericIO-utest)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../lib")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../external/sepVector/lib")

if(BUILD_GCP)
	add_executable( GCPIO GCPIO.cc)
	target_link_libraries(GCPIO   genericCpp buffers gtest gtest_main gtest jsonCpp storage_client tbb ssl)
	add_test(NAME gcpio COMMAND   GCPIO)
else(BUILD_GCP)
endif(BUILD_GCP)


