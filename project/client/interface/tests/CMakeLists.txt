cmake_minimum_required(VERSION 3.14)
project(interface_tests)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-g -O0 -Wall -Wextra -Werror -Wpedantic -fprofile-arcs -ftest-coverage -fPIC -pthread -lgmock")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lpthread -lgtest -coverage -lgcov")


enable_testing(true)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Test Widgets)
find_package(GTest REQUIRED)

set(SOURCE_INTERFACE_TESTS interfaceTest.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../PartyTime)

add_executable(interface_tests ${SOURCE_INTERFACE_TESTS})
target_link_libraries(interface_tests ${API_LIB} ${PAGES_LIB} ${COMPONENTS_LIB} Qt::Test Qt::Core Qt::Gui Qt::Test Qt::Widgets ${GTEST_LIBRARIES})
add_test(NAME interface_tests COMMAND interface_tests)
