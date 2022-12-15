PROJECT(client_server)
cmake_minimum_required(VERSION 3.14)

if (NOT DEFINED MAIN_DIR)
    set(MAIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/.. CACHE PATH MAIN_DIR FORCE)
    include_directories(SYSTEM ${MAIN_DIR}/deps/include)
endif ()

add_subdirectory(server)