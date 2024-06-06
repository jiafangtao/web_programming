cmake_minimum_required(VERSION 3.10)

project (c01)

add_executable(c01 triangles.cpp)

target_link_libraries(c01 PRIVATE ${OPENGL_LIBRARIES})
