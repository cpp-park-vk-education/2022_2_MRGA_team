cmake_minimum_required(VERSION 3.14)
project(interface_tests)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-g -O0 -Wall -Wextra -Werror -Wpedantic -fprofile-arcs -ftest-coverage -fPIC -pthread")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov")

enable_testing()
find_package(GTest REQUIRED)

set(SOURCE_INTERFACE_TESTS interfaceTest.cpp)

add_executable(interface_tests ${SOURCE_INTERFACE_TESTS})
target_link_libraries(interface_tests ${PAGES_LIB} ${API_LIB} ${COMPONENTS_LIB} ${GTEST_LIBRARIES})
