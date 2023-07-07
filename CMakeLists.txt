cmake_minimum_required(VERSION 3.16)
project(compound_traits)
set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEST ${CMAKE_CURRENT_SOURCE_DIR}/test)
set(CMAKE_CXX_STANDARD 17)
include_directories(${SRC})

add_executable(test
    ${TEST}/test.cpp
)
