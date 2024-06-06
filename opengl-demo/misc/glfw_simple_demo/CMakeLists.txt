cmake_minimum_required(VERSION 3.10)

project (opengl-demo-misc VERSION 1.0.410)

find_package(OpenGL REQUIRED)
message("OPENGL_INCLUDE_DIR: ${OPENGL_INCLUDE_DIR}")
message("OPENGL_INCLUDE_DIRS: ${OPENGL_INCLUDE_DIRS}")
message("OPENGL_LIBRARIES: ${OPENGL_LIBRARIES}")
message("OPENGL_glu_LIBRARY: ${OPENGL_glu_LIBRARY}")
message("OPENGL_opengl_LIBRARY: ${OPENGL_opengl_LIBRARY}")


add_executable(glfw_simple_demo ${SRC})
