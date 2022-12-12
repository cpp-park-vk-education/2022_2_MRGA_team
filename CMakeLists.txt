cmake_minimum_required(VERSION 3.14)
PROJECT(PartyTime)
SET(MAIN_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "MAIN_DIR")
set(CMAKE_CXX_STANDARD 20)

include_directories(SYSTEM /usr/local/include)

add_subdirectory(tests)
add_subdirectory(deps)
add_subdirectory(project)

