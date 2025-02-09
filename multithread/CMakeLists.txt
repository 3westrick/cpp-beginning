cmake_minimum_required(VERSION 3.30)
project(multithread)

set(CMAKE_CXX_STANDARD 20)

add_executable(multithread main.cpp)
add_executable(mut mut.cpp)
add_executable(test test.cpp)
