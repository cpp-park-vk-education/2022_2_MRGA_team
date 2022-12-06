cmake_minimum_required(VERSION 3.18)

project(client)

find_package(Boost REQUIRED)

add_executable(${PROJECT_NAME}
        main.cpp)
