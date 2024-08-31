cmake_minimum_required(VERSION 3.18)

project(JSON_Basic_Tools)

set(CMAKE_CXX_STANDARD 11)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

file (GLOB SOURCES
    ./src/parser/*.cpp
    ./src/parser/*.h
    ./src/json/*.cpp
    ./src/json/*.h
)

add_library(JSON_Basic_Tools SHARED ${SOURCES})
target_include_directories(JSON_Basic_Tools PUBLIC include)