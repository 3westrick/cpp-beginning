cmake_minimum_required(VERSION 3.30)
project(mystack)

set(CMAKE_CXX_STANDARD 20)

add_executable(mystack main.cpp)
add_executable(stack stacklinkedlist.cpp)
