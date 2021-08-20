cmake_minimum_required(VERSION 3.20)
project(encrypt_this)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

include_directories(/usr/local/include)

add_executable(encrypt_this_cxx main.cpp)
add_executable(encrypt_this_c main.c)

