cmake_minimum_required(VERSION 3.20)
project(codewars)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

# Find boost to Boost::Test (header only)
find_package(Boost REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

# Get all katas subdirectory automatically
set(KATAS_DIR ${CMAKE_SOURCE_DIR}/katas)
file(GLOB children RELATIVE ${KATAS_DIR} ${KATAS_DIR}/*)
foreach(child ${children})
    if(IS_DIRECTORY ${KATAS_DIR}/${child})
        add_subdirectory(${KATAS_DIR}/${child})
    endif()
endforeach()
