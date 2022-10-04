cmake_minimum_required(VERSION 3.24)
project(connector)

set(Include_dir ${CMAKE_CURRENT_SOURCE_DIR}/interface/
        ${CMAKE_CURRENT_SOURCE_DIR}/implementation)

if (NOT DEFINED(${MAIN_DIR}))
    set(MAIN_DIR ${CMAKE_SOURCE_DIR}/../../../.. CACHE PATH MAIN_DIR FORCE)
    message("MAIN_DIR: ${MAIN_DIR}\n\n")
endif ()

set(deps_include_dir ${MAIN_DIR}/deps/include)
message("deps_include_dir: ${deps_include_dir}\n\n")

include_directories(${Include_dir} ${deps_include_dir})


file(GLOB SOURCES implementation/source/*.cpp)

add_library(${PROJECT_NAME} ${SOURCES})

message("SOURCES = ${SOURCES}, \n Include_dir = ${Include_dir} \n deps_include_dir = ${deps_include_dir}")