cmake_minimum_required(VERSION 3.18)
project(project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

SET(MAIN_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "MAIN_DIR")

include_directories(SYSTEM /usr/local/include)

link_directories(/usr/local/lib)
link_libraries(pq pqxx)
include_directories(SYSTEM /usr/local/include)

add_subdirectory(project)