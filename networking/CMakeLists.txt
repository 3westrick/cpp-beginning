cmake_minimum_required(VERSION 3.30)
project(networking)

set(CMAKE_CXX_STANDARD 20)

add_executable(networking main.cpp)
add_executable(client client.cpp)
add_executable(server server.cpp)
