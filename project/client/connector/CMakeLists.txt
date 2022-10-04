cmake_minimum_required(VERSION 3.24)
PROJECT(connector)
set(CMAKE_CXX_STANDARD 20)

if (NOT DEFINED(${MAIN_DIR}))
    set(MAIN_DIR ${CMAKE_SOURCE_DIR}/../../.. CACHE PATH MAIN_DIR FORCE)
    message("MAIN_DIR: ${MAIN_DIR}\n\n")
endif ()

add_subdirectory(lib)
