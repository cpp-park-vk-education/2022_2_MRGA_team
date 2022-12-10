project(connector_test)
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

set(Include_dir ${PartyTimeConnectorIncludeDirs} ${HTTPConnectorIncludeDirs} ${LocalStorageIncludeDirs})

message("include dirs: ${PartyTimeConnectorIncludeDirs}\n\n")

if (NOT DEFINED MAIN_DIR)
    set(MAIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../.. CACHE PATH MAIN_DIR FORCE)
    message("MAIN_DIR in connector lib dir: ${MAIN_DIR}\n\n")
endif ()

set(deps_include_dir ${MAIN_DIR}/deps/include)

include_directories(${deps_include_dir} ${Include_dir})

AUX_SOURCE_DIRECTORY(src SOURCES)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
        ${PartyTimeConnectorLibs}
        ${GTEST_BOTH_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT})

if (WITH_MEMCHECK)
    message("ADDING VALGRIND COMMAND")
    ADD_TEST(
            NAME TEST_WITH_VALGRIND
            COMMAND ${CMAKE_SOURCE_DIR}/scripts/memtest.sh ./${PROJECT_NAME}
    )
else()
gtest_discover_tests(${PROJECT_NAME})
endif()