cmake_minimum_required(VERSION 3.22)
project(ASCIIart)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE MinSizeRel)
endif ()

if (MSVC)
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /DEBUG")
else ()
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -Wextra -Wpedantic -ggdb -O0")
endif ()

set(CMAKE_CXX_STANDARD 11)

# ncurses
if (MSVC)
    add_subdirectory(libs/PDCurses)
else ()
    find_package(Curses REQUIRED)
    include_directories(${CURSES_INCLUDE_DIR})
endif ()

# sources
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADERS ${CMAKE_SOURCE_DIR}/src/*.hpp)
add_executable(ASCIIart ${SOURCES} ${HEADERS})

if (MSVC)
    target_link_libraries(ASCIIart PRIVATE PDCurses winmm.lib)
else ()
    find_library(CURSES_PANEL_LIBRARY panel)
    target_link_libraries(ASCIIart PRIVATE ${CURSES_LIBRARIES} ${CURSES_PANEL_LIBRARY})
endif ()
