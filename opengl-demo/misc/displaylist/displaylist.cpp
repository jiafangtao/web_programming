#include <windows.h>

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "linmath.h"

//TODO: https://www.glfw.org/docs/latest/quick.html#quick_key_input


typedef struct Vertex
{
    vec2 pos; // position in 2d
    vec3 col; // color (RGB)
} Vertex;

static const Vertex vertices[3] =
{
    { { -0.6f, -0.4f }, { 1.f, 0.f, 0.f } },
    { {  0.6f, -0.4f }, { 0.f, 1.f, 0.f } },
    { {   0.f,  0.6f }, { 0.f, 0.f, 1.f } }
};

static const char* vertex_shader_text =
"#version 330\n"
"uniform mat4 MVP;\n"
"uniform int ptSize;\n"
"in vec3 vCol;\n"
"in vec2 vPos;\n"
"out vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
"    gl_PointSize = 10;\n"
"    color = vCol;\n"
"}\n";

static const char* fragment_shader_text =
"#version 330\n"
"in vec3 color;\n"
"out vec4 fragment;\n"
"void main()\n"
"{\n"
"    fragment = vec4(color, 1.0);\n"
"}\n";

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
    if (window == nullptr) 
        return;
    if (glfwGetCurrentContext() != window) 
        return;

    glViewport(0, 0, width, height);
}

struct Initializer
{
    Initializer() {
        if (!glfwInit())
        {
            // Initialization failed
            throw "glftInit() failed";
        }
    }

    ~Initializer()
    {
        glfwTerminate();
    }
};

// turn on this flag to enable display list demos.
bool flag_dl = false;

int main(int argc, char** argv)
{
    Initializer glfw;

    glfwSetErrorCallback(error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    GLFWwindow* window = glfwCreateWindow(640, 480, "Demo - display list", NULL, NULL);
    //GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL - fullscreen", glfwGetPrimaryMonitor(), nullptr); // Fullscreen
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

    glfwSetFramebufferSizeCallback(window, resize_callback);

    const GLubyte * ver = glGetString(GL_VERSION);

    if (ver != nullptr) {
        std::cout << "version: " << ver << std::endl;
    }

    if (flag_dl) {
        GLuint dl = glGenLists(1);

        if (dl == 0)
        {
            GLenum err = glGetError();
            if (err == GL_INVALID_OPERATION) {
                return 20;
            }
        }

        glNewList(dl, GL_COMPILE);

        GLboolean valid = glIsList(dl);
        if (!valid) {
            return 21;
        }

        glBegin(GL_LINE_LOOP);

        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, 0.0);
        glVertex3f(0.0, 1.0, 0.0);

        glEnd();

        glEndList();

        glCallList(dl);

        GLenum err = glGetError();
        if (err != 0) {
            return 22;
        }
    }

    glfwSwapInterval(1);

    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);

    const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);

    const GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    const GLint mvp_location = glGetUniformLocation(program, "MVP");
    const GLint vpos_location = glGetAttribLocation(program, "vPos");
    const GLint vcol_location = glGetAttribLocation(program, "vCol");

    const GLint ptSize_location = glGetUniformLocation(program, "ptSize");

    GLuint vertex_array;
    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);
    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
        sizeof(Vertex), (void*)offsetof(Vertex, pos));
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
        sizeof(Vertex), (void*)offsetof(Vertex, col));

    while (!glfwWindowShouldClose(window))
    {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        const float ratio = width / (float)height;

        std::cout << "glViewport: w=" << width << ", h=" << height << std::endl;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);


        mat4x4 m, p, mvp;
        mat4x4_identity(m);
        mat4x4_rotate_Z(m, m, (float)glfwGetTime());
        mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        mat4x4_mul(mvp, p, m);

        glUseProgram(program);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)&mvp);
        //glBindVertexArray(vertex_array);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    return 0;
}
