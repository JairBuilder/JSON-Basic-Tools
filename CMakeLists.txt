cmake_minimum_required(VERSION 3.18)

project(JSON_Basic_Tools)

set(CMAKE_CXX_STANDARD 11)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

include_directories(./)

file(GLOB_RECURSE SOURCES "src/*.*")


#add_executable(main ${SOURCES} ./test/test_generator.cpp)
add_executable(main ${SOURCES} ./test/test_parser.cpp)
