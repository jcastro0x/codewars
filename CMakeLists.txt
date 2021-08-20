cmake_minimum_required(VERSION 3.20)
project(codewars)

set(CMAKE_CXX_STANDARD 17)

MACRO(SUBDIRLIST result curdir)
    FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
    SET(dirlist "")
    FOREACH(child ${children})
        IF(IS_DIRECTORY ${curdir}/${child})
            LIST(APPEND dirlist ${child})
        ENDIF()
    ENDFOREACH()
    SET(${result} ${dirlist})
ENDMACRO()

SUBDIRLIST(SUBDIRS ${CMAKE_SOURCE_DIR}/katas)
FOREACH(subdir ${SUBDIRS})
    ADD_SUBDIRECTORY(katas/${subdir})
ENDFOREACH()

