cmake_minimum_required(VERSION 3.10)

project (Tut01 VERSION 1.0)

configure_file(TutorialConfig.h.in TutorialConfig.h)

add_executable(Tut01 tutorial.cpp)

#message("dbg: PROJECT_BINARY_DIR=${PROJECT_BINARY_DIR}")
target_include_directories(Tut01 PUBLIC ${PROJECT_BINARY_DIR})
