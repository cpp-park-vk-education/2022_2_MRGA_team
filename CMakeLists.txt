cmake_minimum_required(VERSION 3.18)
project(project)

set(CMAKE_CXX_STANDARD 23)

find_package(Boost 1.81.0 REQUIRED)

add_subdirectory(server)
add_subdirectory(client)