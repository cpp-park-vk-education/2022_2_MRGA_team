cmake_minimum_required(VERSION 3.14)
project(test_postgres)

find_package(GTest REQUIRED)

set(MY_SRC_FILES *.cpp)

file(GLOB SOURCES ${MY_SRC_FILES})

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC  ${POSTGRES_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${POSTGRES_LIB_LIBRARIES} ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

gtest_discover_tests(${PROJECT_NAME})