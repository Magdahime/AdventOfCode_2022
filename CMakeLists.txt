cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER g++)

set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -Werror -Wpedantic")

project(AdventOfCode2022 VERSION 1.0
        DESCRIPTION "Advent of Code 2022"
        LANGUAGES CXX)

set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/bin/)
set(HEADER_DIRECTORY ${PROJECT_SOURCE_DIR}/include/)
set(SOURCE_DIRECTORY ${PROJECT_SOURCE_DIR}/src/)
set(PUZZLE_DIRECTORY ${SOURCE_DIRECTORY}/Puzzles/)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})

include_directories(${HEADER_DIRECTORY})



set(SOURCES ${PUZZLE_DIRECTORY}/puzzle1.cpp
            ${PUZZLE_DIRECTORY}/puzzle2.cpp
            ${SOURCE_DIRECTORY}/Program.cpp
            ${SOURCE_DIRECTORY}/main.cpp
            ${SOURCE_DIRECTORY}/FileReader.cpp
            )

add_executable(AdventOfCode2022 ${SOURCES})
