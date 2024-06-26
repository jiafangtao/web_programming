#ifndef COMMON_H
#define COMMON_H

#include "linmath.h"
#include <glad/glad.h>

typedef struct Vertex
{
    vec2 pos; // position in 2d
    vec3 col; // color (RGB)
} Vertex;

struct Initializer
{
    Initializer();
    ~Initializer();
};


bool checkError(const char* fileName, int line);

void drawLineLoop(GLuint dl);
void drawPolygon(GLuint dl);
void drawColorbar(GLuint dl);

#endif
