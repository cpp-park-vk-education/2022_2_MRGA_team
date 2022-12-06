cmake_minimum_required(VERSION 3.18)

project(client)

find_package(Boost 1.81.0 REQUIRED REQUIRED COMPONENTS container)

add_executable(${PROJECT_NAME}
        main.cpp)
