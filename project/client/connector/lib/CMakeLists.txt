cmake_minimum_required(VERSION 3.24)
project(connector)

set(Include_dir ${CMAKE_CURRENT_SOURCE_DIR}/interface/
        ${CMAKE_CURRENT_SOURCE_DIR}/implementation)

set(deps_include_dir ${MAIN_DIR}/deps/include)

if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(deps_include_dir ${CMAKE_SOURCE_DIR}/../../../../deps/include)
    message(STATUS "deps include dir: ${deps_include_dir}")
endif ()

include_directories(${Include_dir} ${deps_include_dir})


file(GLOB SOURCES implementation/source/*.cpp)

add_library(${PROJECT_NAME} ${SOURCES})

message("SOURCES = ${SOURCES}, \n Include_dir = ${Include_dir} \n deps_include_dir = ${deps_include_dir}")