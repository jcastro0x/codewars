cmake_minimum_required(VERSION 3.20)
project(convert_string_to_camel_case)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/local/include)

add_executable(convert_string_to_camel_case main.cpp)