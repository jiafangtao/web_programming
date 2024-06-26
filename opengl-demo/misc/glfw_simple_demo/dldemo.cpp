#include <windows.h>

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "linmath.h"
#include "common.h"


void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    else if (key == GLFW_KEY_B && action == GLFW_PRESS)
    {
        // make point bigger
        std::cout << "TODO: make point bigger" << std::endl;

        //TODO: fix this later
        //glUniform1i(ptSize_location, 10);
    }
    else if (key == GLFW_KEY_S && action == GLFW_PRESS)
    {
        // make point smaller
        std::cout << "TODO: make point smaller" << std::endl;

        //TODO: fix this later
        //glUniform1i(ptSize_location, 2);
    }
}

// GLFWframebuffersizefun
void resize_callback(GLFWwindow* window, int width, int height)
{
    if (window == nullptr || glfwGetCurrentContext() != window) 
        return;

    glViewport(0, 0, width, height);
}

int main(int argc, char** argv)
{
    Initializer glfw;

    glfwSetErrorCallback(error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    GLFWwindow* window = glfwCreateWindow(640, 480, "Demo - display list", NULL, NULL);
    //GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL - fullscreen", glfwGetPrimaryMonitor(), nullptr); // Fullscreen doesn't work
    if (!window)
    {
        // Window or OpenGL context creation failed
        return 2;
    }

    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);

    gladLoadGL();

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    checkError(__FILE__, __LINE__);

    glfwSetFramebufferSizeCallback(window, resize_callback);

    GLuint dlLoop = glGenLists(1);
    checkError(__FILE__, __LINE__);
    std::cout << "display list for line loop: " << dlLoop << std::endl;
    drawLineLoop(dlLoop);

    GLuint dlPolygon = glGenLists(1);
    checkError(__FILE__, __LINE__);
    std::cout << "display list for polygon: " << dlPolygon << std::endl;
    drawPolygon(dlPolygon);

    GLuint dlColorbar = glGenLists(1);
    checkError(__FILE__, __LINE__);
    std::cout << "display list for polygon: " << dlColorbar << std::endl;
    drawColorbar(dlColorbar);

    glfwSwapInterval(1);
    checkError(__FILE__, __LINE__);

    while (!glfwWindowShouldClose(window))
    {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        const float ratio = width / (float)height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        // animate the line width
        float t = float(glfwGetTime());
        float lineWidth = 1 + 10 * abs(sin(t));
        glLineWidth(lineWidth);

        glCallList(dlLoop);
        checkError(__FILE__, __LINE__);

        glCallList(dlPolygon);
        checkError(__FILE__, __LINE__);

        glCallList(dlColorbar);
        checkError(__FILE__, __LINE__);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    return 0;
}
