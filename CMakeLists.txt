cmake_minimum_required(VERSION 3.10)

project(npuzzle)

set(BINARY ${CMAKE_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(extern_lib/googletest_lib)

set(SOURCES
    createpuzzle.cpp
    main.cpp
    Node.cpp
    Node.hpp
    Puzzle.cpp
    Puzzle.hpp
    readfile.cpp
    solvable.cpp
    utils.hpp)

add_executable(${BINARY} ${SOURCES})
add_subdirectory(test)
add_library(${BINARY}_lib STATIC ${SOURCES})

# target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest)