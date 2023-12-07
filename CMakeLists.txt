cmake_minimum_required(VERSION 3.14...3.28)
project(codewars)

enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

#
# Linux hasn't MSVC CRT functions, so don't allow platform-specific code
if(MSVC)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

#
# Dependencies
include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
)

FetchContent_Declare(
    unity
    GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
    GIT_TAG        v2.5.2
)

FetchContent_MakeAvailable(googletest unity)

#
# Look for projects into @KATAS_DIR directory and add it as subdirectory.
# Once added, link libraries @TEST_LIB to it.
function(AddKatas KATAS_DIR TEST_LIB)
    file(GLOB children RELATIVE ${KATAS_DIR} ${KATAS_DIR}/*)
    foreach(child ${children})
        if(IS_DIRECTORY ${KATAS_DIR}/${child})
            add_subdirectory(${KATAS_DIR}/${child})
            target_link_libraries(${child} ${TEST_LIB})
            message(STATUS "Added kata: ${child}")

            add_test(NAME ${child} COMMAND ${child})
        endif()
    endforeach()
endfunction()


message( "##############################################################" )
message( "#                      C++ KATAS                             #" )
message( "##############################################################" )
AddKatas(${CMAKE_SOURCE_DIR}/katas/cxx gtest_main)

message( "##############################################################" )
message( "#                       C KATAS                              #" )
message( "##############################################################" )
AddKatas(${CMAKE_SOURCE_DIR}/katas/c unity)
