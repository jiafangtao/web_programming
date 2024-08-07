/*********************************************************************************************/
/*    Single triangle shown in multiple mode - demonstrate usage of multiple shaders         */
/*********************************************************************************************/


#include <windows.h>

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <assert.h>
#include "linmath.h"
#include "common.h"
#include "JProgram.h"
#include "utils.h"


using namespace std;

GLfloat g_pt_size = 1.0f;
GLfloat g_zoom_factor = 1.0f;

GLint zoomFactor_location = 0;

int useShader = 1;
GLint vertex_shader_1, vertex_shader_2;
GLuint program;

/*
static Vertex vertices[3] =
{
    // data shape:
    // position (x, y), color (r, g, b)
    { { -0.6f, -0.4f }, { 1.f, 0.f, 0.f } },
    { {  0.6f, -0.4f }, { 0.f, 1.f, 0.f } },
    { {   0.f,  0.6f }, { 0.f, 0.f, 1.f } }
};
*/

static Vertex vertices[3] =
{
    { -0.6f, -0.4f, 0.0f },
    {  0.6f, -0.4f, 0.0f },
    {  0.f,   0.6f, 0.0f }
};

// This demo uses two vertex shaders to show a triangle: 
// one shader renders the triangle with gradient colors, the other
// redners the triangle in white.

static const char* vertex_shader_text_1 =
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


// No color effect for this shader
static const char* vertex_shader_text_2 =
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
"    color = vec3(1.0, 1.0, 1.0);//white\n"
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
    else if ((key == GLFW_KEY_F7) && action == GLFW_PRESS)
    {
        cout << "Key F7: zoom in" << endl;
        g_zoom_factor *= 2.0f;
        glUniform1f(zoomFactor_location, g_zoom_factor);
    }
    else if ((key == GLFW_KEY_F8) && action == GLFW_PRESS)
    {
        cout << "Key F8: zoom out" << endl;
        g_zoom_factor /= 2.0f;
        glUniform1f(zoomFactor_location, g_zoom_factor);
    }
    else if ((key == GLFW_KEY_F10) && action == GLFW_PRESS)
    {
        cout << "Key F10: switch render type (colorful or colorless)" << endl;
        if (useShader == 2) {
            glDetachShader(program, vertex_shader_2);
            glAttachShader(program, vertex_shader_1);
            glLinkProgram(program);
            glUseProgram(program);

            useShader = 1;
        } else if (useShader == 1) {
            glDetachShader(program, vertex_shader_1);
            glAttachShader(program, vertex_shader_2);
            glLinkProgram(program);
            glUseProgram(program);
            
            useShader = 2;
        }
    }
}

// GLFWframebuffersizefun
inline void resize_callback(GLFWwindow* window, int width, int height)
{
    if (window == nullptr) 
        return;
    if (glfwGetCurrentContext() != window) 
        return;

    glViewport(0, 0, width, height);
}


int main(int argc, char** argv)
{
    Initializer glfw;

    glfwSetErrorCallback(error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(640, 480, "Demo - Single Triangle", NULL, NULL);
    if (!window) { return 2; }

    glfwSetKeyCallback(window, key_callback);

    // Make the OpenGL context current. This is important and most be called after load GL (via glad or alternatives)
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }

    // glad populates global constants after loading to indicate,
    // if a certain extension/version is available.
    printf("OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glfwSetFramebufferSizeCallback(window, resize_callback);
    glfwSwapInterval(1);

    // IMPORTANT: this feature must be enabled to set point size.
    glEnable(GL_PROGRAM_POINT_SIZE);

    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    vertex_shader_1 = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader_1, 1, &vertex_shader_text_1, NULL);
    glCompileShader(vertex_shader_1);

    vertex_shader_2 = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader_2, 1, &vertex_shader_text_2, NULL);
    glCompileShader(vertex_shader_2);

    const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);

    program = glCreateProgram();
    // vs 1 is the default shader.
    glAttachShader(program, vertex_shader_1);
    
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    const GLint mvp_location = glGetUniformLocation(program, "MVP");
    const GLint vpos_location = glGetAttribLocation(program, "vPos");
    const GLint vcol_location = glGetAttribLocation(program, "vCol");

    GLint ptSize_location = glGetUniformLocation(program, "ptSize");
    GLint zoomFactor_location = glGetUniformLocation(program, "zoomFactor");
    GLint colorFactor_location = glGetUniformLocation(program, "colorFactor");
    cout << "(dbg) colorFactor loc: " << colorFactor_location << endl;

    GLuint vertex_array;
    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);
    
    glEnableVertexAttribArray(vpos_location);

    //glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
    //    sizeof(Vertex), (void*)offsetof(Vertex, pos));
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
        sizeof(Vertex), (void*)0);
    
    glEnableVertexAttribArray(vcol_location);

    //glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
        //sizeof(Vertex), (void*)offsetof(Vertex, col));
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
        sizeof(Vertex), (void*)0);

    float bbox[4] = { 0.0f };
    util::bbox(vertices, 6, bbox);
    const float factor = max(abs(bbox[0] - bbox[2]), abs(bbox[1] - bbox[3]));

    while (!glfwWindowShouldClose(window))
    {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        const float ratio = width / (float)height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        mat4x4 m, p, mvp;
        mat4x4_identity(m);

        mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        mat4x4_scale_aniso(m, m, 1.0f / factor, 1.0f / factor, 1);
        
        mat4x4_mul(mvp, p, m);

        glUseProgram(program);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)&mvp);

        //NOTE: initialize these to shaders otherwise default values will be used, which
        // may be not what we expected. And it seems this doesn't work if we do this before 
        // call glUseProgram.
        glUniform1f(ptSize_location, g_pt_size);
        glUniform1f(zoomFactor_location, g_zoom_factor);

        // draw the points
        glDrawArrays(GL_POINTS, 0, 3);
        checkError(__FILE__, __LINE__);

        colorFactor_location = glGetUniformLocation(program, "colorFactor");
        checkError(__FILE__, __LINE__);

        if (colorFactor_location != GL_INVALID_VALUE) {
            glUniform1f(colorFactor_location, 1);
        }
        
        checkError(__FILE__, __LINE__);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        checkError(__FILE__, __LINE__);

        glfwSwapBuffers(window);
        glfwPollEvents();
    } //end of loop
    
    glfwDestroyWindow(window);
    return 0;
}
