cmake_minimum_required(VERSION 3.18)

project(CPP)

add_executable(main main.cpp)
target_compile_features(main PRIVATE cxx_std_17)