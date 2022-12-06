cmake_minimum_required(VERSION 3.18)
project(project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(project/client)
add_subdirectory(project/server)