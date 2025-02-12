cmake_minimum_required(VERSION 3.30)
project(ChatServerTCP)

set(CMAKE_CXX_STANDARD 20)

add_executable(server main.cpp)
add_executable(client client.cpp)
add_executable(test_server test_server.cpp)
add_executable(test_client test_client.cpp)
