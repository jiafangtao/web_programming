#include "common.h"
#include <string>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


Initializer::Initializer() {
    if (!glfwInit())
    {
        // Initialization failed
        throw "glftInit() failed";
    }
}

Initializer::~Initializer()
{
    glfwTerminate();
}

/**
 * Check the current GL error.
 * Returns true if no error was detected; returns false if there was an error.
 */
bool checkError(const char* fileName, int line) {

    GLenum e = glGetError();
    std::string msg;

    switch (e)
    {
    case GL_NO_ERROR:
        // do nothing if no errors
        return true;
    case GL_INVALID_ENUM:
        msg = "GL_INVALID_ENUM";
        break;
    case GL_INVALID_VALUE:
        msg = "GL_INVALID_VALUE";
        break;
    case GL_INVALID_OPERATION:
        msg = "GL_INVALID_OPERATION";
        break;
    case GL_STACK_OVERFLOW:
        msg = "GL_STACK_OVERFLOW";
        break;
    case GL_STACK_UNDERFLOW:
        msg = "GL_STACK_UNDERFLOW";
        break;
    case GL_OUT_OF_MEMORY:
        msg = "GL_OUT_OF_MEMORY";
        break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
        msg = "GL_INVALID_FRAMEBUFFER_OPERATION";
        break;
    default:
        break;
    }

    std::cout << msg << " | " << fileName << "(" << line << ")" << std::endl;
    return false;
}


void drawLineLoop(GLuint dl) {

    glNewList(dl, GL_COMPILE);
    checkError(__FILE__, __LINE__);

    glBegin(GL_LINE_LOOP);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);
    glEnd();

    glEndList();
}

void drawPolygon(GLuint dl) {
    glNewList(dl, GL_COMPILE);
    checkError(__FILE__, __LINE__);

    glBegin(GL_POLYGON);
    //glColor4ub(255, 0, 0, 150);
    glVertex3f(-1.0, 0.0, 0.0);

    //glColor4ub(0, 255, 0, 150);
    glVertex3f(0.0, 0.0, 0.0);
    
    //glColor4ub(0, 255, 0, 150);
    glVertex3f(0.0, 1.0, 0.0);
    
    //glColor4ub(255, 0, 0, 150);
    glVertex3f(-1.0, 1.0, 0.0);
    glEnd();

    glColor4ub(255, 255, 255, 255);

    checkError(__FILE__, __LINE__);

    glEndList();
}

void drawColorbar(GLuint dl) {
    glNewList(dl, GL_COMPILE);
    checkError(__FILE__, __LINE__);

    glBegin(GL_POLYGON);
    unsigned char alpha = 100;
    
    glColor4ub(255, 0, 0, alpha); // red point
    glVertex3f(-1.0, 0.0, 0.0);

    glColor4ub(0, 0, 255, alpha); // blue point
    glVertex3f(-0.5, 0.0, 0.0);

    /*
    glColor4ub(0, 255, 0, alpha); // green point
    glVertex3f(0.0, 0.0, 0.0);

    glColor4ub(0, 255, 0, alpha); // green point
    glVertex3f(0.0, 0.1, 0.0);
    */

    glColor4ub(0, 0, 255, alpha); // blue point
    glVertex3f(-0.5f, 0.1f, 0.0f);

    glColor4ub(255, 0, 0, alpha); // red point
    glVertex3f(-1.0f, 0.1f, 0.0f);

    glEnd();

    // reset color to default
    glColor4ub(255, 255, 255, 255);

    checkError(__FILE__, __LINE__);

    glEndList();
}

void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}
