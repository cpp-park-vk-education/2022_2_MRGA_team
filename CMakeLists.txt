cmake_minimum_required(VERSION 3.18)
project(project)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost REQUIRED)

add_subdirectory(json_struct_mapping)
add_subdirectory(server)
add_subdirectory(client)