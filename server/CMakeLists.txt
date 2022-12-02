cmake_minimum_required(VERSION 3.18)

project(server)

find_package(Boost 1.81.0 REQUIRED)

add_executable(${PROJECT_NAME}
        server/http_connection.cpp
        server/http_connection.hpp

        server/tcp_server.cpp
        server/tcp_server.hpp

        server/router.cpp
        server/router.hpp

        main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE Boost::url)
