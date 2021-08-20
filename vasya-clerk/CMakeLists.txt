cmake_minimum_required(VERSION 3.20)
project(vasya_clerk)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/local/include)

add_executable(vasya_clerk main.cpp)