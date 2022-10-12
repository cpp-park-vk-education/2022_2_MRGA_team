cmake_minimum_required(VERSION 3.14)
project(interface_tests)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-g -O0 -Wall -Wextra -Werror -Wpedantic -fprofile-arcs -ftest-coverage -fPIC -pthread")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov")

enable_testing()
find_package(GTest REQUIRED)

set(SOURCE_SYNC_TESTS sync_test.cpp)
set(SOURCE_ASYNC_TESTS async_test.cpp)

add_executable(sync_tests ${SOURCE_SYNC_TESTS})
target_link_libraries(sync_tests ${SYNC_MATRIX_LIB_LIBRARIES} ${GTEST_LIBRARIES})

add_executable(async_tests ${SOURCE_ASYNC_TESTS})
target_link_libraries(async_tests ${ASYNC_MATRIX_LIB_LIBRARIES} ${GTEST_LIBRARIES})