cmake_minimum_required(VERSION 3.24)
PROJECT(PartyTime)
SET(MAIN_DIR ${CMAKE_SOURCE_DIR} CACHE INTERNAL "MAIN_DIR")
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(deps)
add_subdirectory(project)