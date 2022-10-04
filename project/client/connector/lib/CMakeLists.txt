cmake_minimum_required(VERSION 3.24)
project(connector)

set(Include_dir ${CMAKE_CURRENT_SOURCE_DIR}/interface/
        ${CMAKE_CURRENT_SOURCE_DIR}/implementation)


include_directories(${Include_dir})

file(GLOB SOURCES implementation/source/*.cpp)



add_library(${PROJECT_NAME} ${SOURCES})

message("SOURCES = ${SOURCES}, \n Include_dir = ${Include_dir}")
