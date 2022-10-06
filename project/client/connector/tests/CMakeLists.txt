project(connector_test)
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

set(Include_dir ${CMAKE_CURRENT_SOURCE_DIR}/../lib/interface/
        ${CMAKE_CURRENT_SOURCE_DIR}/../lib/implementation)

if (NOT DEFINED MAIN_DIR)
    set(MAIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../.. CACHE PATH MAIN_DIR FORCE)
    message("MAIN_DIR in connector lib dir: ${MAIN_DIR}\n\n")
endif ()

set(deps_include_dir ${MAIN_DIR}/deps/include)

include_directories(${deps_include_dir} ${Include_dir})

file(GLOB SOURCES src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} connector ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

gtest_discover_tests(${PROJECT_NAME})
