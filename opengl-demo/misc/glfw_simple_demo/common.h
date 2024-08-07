#ifndef COMMON_H
#define COMMON_H

#include "linmath.h"
#include <glad/glad.h>

// initialize OpenGL
struct Initializer {
    Initializer();
    ~Initializer();
};


bool checkError(const char* fileName, int line);

void drawLineLoop(GLuint dl);
void drawPolygon(GLuint dl);
void drawColorbar(GLuint dl);

void error_callback(int error, const char* description);

#endif
