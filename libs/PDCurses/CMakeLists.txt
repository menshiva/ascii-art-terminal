cmake_minimum_required(VERSION 3.22)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_LIST_DIR}/*.c)
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_LIST_DIR}/*.h)

add_library(PDCurses ${SOURCES} ${HEADERS})

target_include_directories(PDCurses PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
