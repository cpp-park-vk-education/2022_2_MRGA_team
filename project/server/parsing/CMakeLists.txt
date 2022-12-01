cmake_minimum_required(VERSION 3.18)
project(project)

set(CMAKE_CXX_STANDARD 20)

message("PARSING_LIB_INCLUDE_DIRS = ${PARSING_LIB_INCLUDE_DIRS}")
message("PARSING_LIB_LIBRARIES = ${PARSING_LIB_LIBRARIES}")

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${PARSING_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${PARSING_LIB_LIBRARIES})