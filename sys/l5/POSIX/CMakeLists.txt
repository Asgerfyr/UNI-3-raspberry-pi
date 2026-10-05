cmake_minimum_required(VERSION 3.0...3.20)

project(grid VERSION 1.0
            DESCRIPTION "Grid project"
            LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CPP_COMPILER g++)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build/bin")

set(SRC main.cpp)

add_executable(main.out ${SRC})




#message(STATUS "DEBUG: ${CMAKE_BINARY_DIR}")