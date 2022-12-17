cmake_minimum_required(VERSION 3.14)
project(handler_lib)

include_directories(SYSTEM ${MAIN_DIR}/deps/include)


link_directories(/usr/local/lib)
link_libraries(pq pqxx)
include_directories(SYSTEM /usr/local/include)

add_subdirectory(service)



message("SERVICE_LIB_LIBRARIES = " ${SERVICE_LIB_LIBRARIES})
message("SERVICE_LIB_INCLUDE_DIRS = " ${SERVICE_LIB_INCLUDE_DIRS})

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/**/*.cpp)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})

set(HANDLER_LIB_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(HANDLER_LIB_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)

target_include_directories(${PROJECT_NAME} PUBLIC ${SERVICE_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${SERVICE_LIB_LIBRARIES})