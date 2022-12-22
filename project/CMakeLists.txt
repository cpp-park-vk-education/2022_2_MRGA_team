PROJECT(client_server)
cmake_minimum_required(VERSION 3.14)

include_directories(SYSTEM ${MAIN_DIR}/deps/include)
include_directories(SYSTEM /usr/local/include)
include_directories(SYSTEM /opt/homebrew/include)
link_directories(/opt/homebrew/lib)

if (NOT DEFINED MAIN_DIR)
    set(MAIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/.. CACHE PATH MAIN_DIR FORCE)
    include_directories(SYSTEM ${MAIN_DIR}/deps/include)
endif ()

link_directories(/usr/local/lib)
# link_libraries(pq pqxx)
include_directories(SYSTEM /usr/local/include)

add_subdirectory(server)
