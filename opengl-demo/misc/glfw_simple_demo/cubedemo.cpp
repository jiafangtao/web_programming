#include <windows.h>

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
//#include <assert.h>
//#include "linmath.h"
//#include "common.h"

#include "JProgram.h"
#include <vector>

using namespace std;


//TODO: general shaders for all the scene objects?

static const char* vertex_shader_text =
"#version 330\n"
"#pragma debug(on)\n"
"uniform mat4 MVP;\n"
"uniform float ptSize;\n"
"uniform float zoomFactor;\n"
"uniform float colorFactor;\n"
"in vec3 vCol;\n"
"in vec2 vPos;\n"
"out vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(zoomFactor, zoomFactor, 0.0, 1.0) * MVP * vec4(vPos, 0.0, 1.0);\n"
"    gl_PointSize = ptSize;\n"
"    color = colorFactor * vCol;\n"
"}\n";

static const char* fragment_shader_text =
"#version 330\n"
"in vec3 color;\n"
"out vec4 fragment;\n"
"void main()\n"
"{\n"
"    fragment = vec4(color, 1.0);\n"
"}\n";


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    else if (key == GLFW_KEY_B && action == GLFW_PRESS)
    {
        //glUniform1f(ptSize_location, g_pt_size);
    }
    else if (key == GLFW_KEY_S && action == GLFW_PRESS)
    {
        //glUniform1f(ptSize_location, g_pt_size);
    }
    else if ((key == GLFW_KEY_7 || key == GLFW_KEY_F7) && action == GLFW_PRESS)
    {
        //glUniform1f(zoomFactor_location, g_zoom_factor);
    }
    else if ((key == GLFW_KEY_8 || key == GLFW_KEY_F8) && action == GLFW_PRESS)
    {
        //glUniform1f(zoomFactor_location, g_zoom_factor);
    }
    else if (key == GLFW_KEY_A && action == GLFW_PRESS)
    {
        // key 'a' for animation
        // animation 1 - change triangle #2 color
        cout << "Key A: animating triangle #2 color" << endl;
    }
    else if (key == GLFW_KEY_D && action == GLFW_PRESS)
    {
        // key 'd' for debug
        cout << "Key D: checking the viewport ..." << endl;
        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);
        cout << "  " << viewport[0] << ", " << viewport[1] << ", " << viewport[2] << ", " << viewport[3] << endl;
    }
}
