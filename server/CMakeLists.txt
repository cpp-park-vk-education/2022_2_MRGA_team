cmake_minimum_required(VERSION 3.18)

project(server)

add_subdirectory(lib)
add_subdirectory(json_struct_mapping)

find_package(Boost 1.81.0 REQUIRED REQUIRED COMPONENTS container)

add_executable(${PROJECT_NAME}
        server/http_connection.cpp
        server/http_connection.hpp

        server/tcp_server.cpp
        server/tcp_server.hpp

        server/router.cpp
        server/router.hpp

        server/service.cpp
        server/service.hpp

        main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${POSTGRES_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${POSTGRES_LIB_LIBRARIES})

target_include_directories(${PROJECT_NAME} PUBLIC ${PARSING_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${PARSING_LIB_LIBRARIES})
