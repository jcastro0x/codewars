cmake_minimum_required(VERSION 3.20)
project(codewars)

enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

#
# Linux hasn't MSVC CRT functions, so don't allow platform-specific code
if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

#
# Add Google Test
add_subdirectory("libs/googletest")
add_subdirectory("libs/check")

#
# Look for projects into @PATH directory and add it as subdirectory.
# Once added, link libraries @UNIT_TEST to it.
function(AddKatas PATH UNIT_TEST)
    file(GLOB children RELATIVE ${PATH} ${PATH}/*)
    foreach(child ${children})
        if(IS_DIRECTORY ${PATH}/${child})
            add_subdirectory(${PATH}/${child})
            target_link_libraries(${child} ${UNIT_TEST})
            message("Added kata: " ${child})

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
AddKatas(${CMAKE_SOURCE_DIR}/katas/c check)
