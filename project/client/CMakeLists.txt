cmake_minimum_required(VERSION 3.18)
project(Client)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost REQUIRED)

add_executable(${PROJECT_NAME}
        main.cpp)
