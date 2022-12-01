cmake_minimum_required(VERSION 3.18)

project(server)

find_package(Boost REQUIRED)

add_executable(${PROJECT_NAME}
        server/http_connection.cpp
        server/http_connection.hpp

        server/tcp_server.cpp
        server/tcp_server.hpp

        main.cpp)
