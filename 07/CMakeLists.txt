cmake_minimum_required(VERSION 3.10)
project(container_examples)

set(CMAKE_CXX_STANDARD 17)

include_directories(../common)

add_executable(test_line_reader           test_line_reader.cpp)