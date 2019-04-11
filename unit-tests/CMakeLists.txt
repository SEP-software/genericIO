cmake_minimum_required(VERSION 3.1)
project(genericIO-utest)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../lib")

if(BUILD_GCP)
add_executable( GCPtest GCPtest.cc)
target_link_libraries(GCPtest   genericCpp buffers gtest gtest_main gtest jsonCpp storage_client tbb)
add_test(NAME gcp COMMAND   GCPtest)
else(BUILD_GCP)
endif(BUILD_GCP)


