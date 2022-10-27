cmake_minimum_required(VERSION 3.14)
PROJECT(PartyTime)
SET(MAIN_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "MAIN_DIR")
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(project/client/interface/PartyTime)
add_subdirectory(tests)
# add_subdirectory(deps)
# add_subdirectory(project)
