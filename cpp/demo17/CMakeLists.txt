cmake_minimum_required(VERSION 3.22)
project(demo17)

set(CMAKE_CXX_STANDARD 17)

add_executable(demo17 main.cpp TestMMap.cpp TestMMap.h)
add_executable(other demo_inline_static.cpp)

add_library(mylib TestMMap.cpp TestMMap.h)

add_executable(revisit revisit.cpp)

add_executable(crtp crtp.cpp)
