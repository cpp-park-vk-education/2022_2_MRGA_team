cmake_minimum_required(VERSION 3.18)
project(json_struct_mapping_lib CXX)
set(CMAKE_CXX_STANDARD 20)
add_subdirectory(struct_mapping_lib)



file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

add_library(${PROJECT_NAME} INTERFACE ${SOURCES})

add_executable(test main.cpp)
target_include_directories(test PRIVATE struct_mapping_lib)
target_include_directories(test PRIVATE SYSTEM /usr/local/include)

install(FILES structs.hpp DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/../include")
install(FILES structs_error_codes.hpp DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/../include")
