cmake_minimum_required(VERSION 3.9)
project(lab1_cpp)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GTK_CFLAGS} -lboost_regex")

add_executable(lab1_cpp main.cpp)