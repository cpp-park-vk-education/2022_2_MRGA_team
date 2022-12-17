cmake_minimum_required(VERSION 3.18)

project(server LANGUAGES CXX)

include_directories(SYSTEM ${MAIN_DIR}/deps/include)

add_subdirectory(handler)

message("HANDLER_LIB_LIBRARIES = " ${HANDLER_LIB_LIBRARIES})
message("HANDLER_LIB_INCLUDE_DIRS = " ${HANDLER_LIB_INCLUDE_DIRS})

find_package(Boost 1.81.0 REQUIRED REQUIRED COMPONENTS container)

include_directories(${PROJECT_NAME} src/)

# set(MY_CXX_FLAGS "-lpqxx -lpq")
link_libraries(pqxx)
set(CMAKE_CXX_FLAGS ${MY_CXX_FLAGS})

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/**/*.cpp main.cpp)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${HANDLER_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${HANDLER_LIB_LIBRARIES})



target_include_directories(${PROJECT_NAME} PUBLIC ${SERVICE_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${SERVICE_LIB_LIBRARIES})
