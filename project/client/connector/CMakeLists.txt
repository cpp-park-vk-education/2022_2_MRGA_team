cmake_minimum_required(VERSION 3.24)
PROJECT(connector)
set(CMAKE_CXX_STANDARD 20)

if (NOT DEFINED MAIN_DIR)
    set(MAIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../.. CACHE PATH MAIN_DIR FORCE)
    message("MAIN_DIR in connector dir: ${MAIN_DIR}\n\n")
endif ()

add_subdirectory(lib)
