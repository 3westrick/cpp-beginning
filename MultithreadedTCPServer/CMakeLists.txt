cmake_minimum_required(VERSION 3.30)
project(MultithreadedTCPServer)

set(CMAKE_CXX_STANDARD 20)

add_executable(MultithreadedTCPServer main.cpp)
add_executable(client client.cpp)
