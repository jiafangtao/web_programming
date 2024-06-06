#include <windows.h>

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <assert.h>
#include "linmath.h"
#include "common.h"


static const Vertex vertices[10] =
{
    { { -0.6f, -0.4f }, { 1.f, 0.f, 0.f } },
    { {  0.6f, -0.4f }, { 0.f, 1.f, 0.f } },
    { {   0.f,  0.6f }, { 0.f, 0.f, 1.f } },
    { { 3-0.6f, 0.6f }, { 0.f, 0.f, 1.f } },
    { {  3.6f, 0.6f }, { 0.f, 1.f, 0.f } },
    { {  3.f,  -0.4f }, { 1.f, 0.f, 0.f } },

    { {  0.f,  0.f }, { 1.f, 1.f, 0.f } },
    { {  1.f,  0.f }, { 1.f, 1.f, 0.f } },
    { {  1.f,  1.f }, { 1.f, 1.f, 0.f } },
    { {  0.f,  1.f }, { 1.f, 1.f, 0.f } }
};

static const char* vertex_shader_text =
"#version 330\n"
"uniform mat4 MVP;\n"
"uniform float ptSize;\n"
"in vec3 vCol;\n"
"in vec2 vPos;\n"
"out vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
"    gl_PointSize = ptSize;\n"
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

static float g_pt_size = 1.0f;
static GLint ptSize_location = 0;
static bool g_flag_rotating = true;

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
        const float cap_max = 20.0f;
        if (g_pt_size < cap_max) {
            std::cout << "make point bigger" << std::endl;
        }
        else
        {
            std::cout << "point is big enough:" << g_pt_size << std::endl;
        }

        g_pt_size += 1.0f;

        if (g_pt_size > cap_max) {
            g_pt_size = cap_max;
        }
        
        glUniform1f(ptSize_location, g_pt_size);
    }
    else if (key == GLFW_KEY_S && action == GLFW_PRESS)
    {
        const float cap_min = 1.0f;
        if (g_pt_size > cap_min)
        {
            std::cout << "make point smaller" << std::endl;
        }
        else
        {
            std::cout << "point is small enough: " << g_pt_size << std::endl;
        }
        
        g_pt_size -= 1.0f;

        if (g_pt_size < 1.0f) {
            g_pt_size = 1.0f;
        }
        glUniform1f(ptSize_location, g_pt_size);
    }
}

namespace util {
    void bbox(const Vertex* vertices, unsigned int size, float* bb)
    {
        assert(vertices != nullptr);
        assert(size > 0);

        // z is not considered in this case.
        float xmin, xmax, ymin, ymax;
        xmin = xmax = vertices[0].pos[0];
        ymin = ymax = vertices[0].pos[1];
        
        for (unsigned int i = 1; i < size; i++)
        {
            float x = vertices[i].pos[0];
            float y = vertices[i].pos[1];

            if (x < xmin) { xmin = x; }
            if (y < ymin) { ymin = y; }
            if (x > xmax) { xmax = x; }
            if (y > ymax) { ymax = y; }
        }

        bb[0] = xmin;
        bb[1] = ymin;
        bb[2] = xmax;
        bb[3] = ymax;
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

int main(int argc, char** argv)
{
    Initializer glfw;

    glfwSetErrorCallback(error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    GLFWwindow* window = glfwCreateWindow(640, 480, "Demo - Triangles", NULL, NULL);
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
    glfwSwapInterval(1);

    // IMPORTANT: this feature must be enabled to set point size.
    glEnable(GL_PROGRAM_POINT_SIZE);

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

    ptSize_location = glGetUniformLocation(program, "ptSize");

    GLuint vertex_array;
    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);
    
    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
        sizeof(Vertex), (void*)offsetof(Vertex, pos));
    
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
        sizeof(Vertex), (void*)offsetof(Vertex, col));

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
        if (g_flag_rotating) {
            mat4x4_rotate_Z(m, m, (float)glfwGetTime());
            //TODO: I don't know if rotate really change model matrix. should it?
        }
        mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        
        //NOTE: I believe this is not a good way to change the projection matrix.
        // The problem that some shapes are cut off should be caused by the invalid model matrix
        // which was initialized to identity matrix.
        //mat4x4_ortho(p, -ratio * 5, ratio * 5, -5.f, 5.f, 1.f, -1.f);

        // try to tweat the model matrix
        mat4x4_scale_aniso(m, m, 1.0f / factor, 1.0f / factor, 1);
        
        mat4x4_mul(mvp, p, m);

        glUseProgram(program);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)&mvp);

        // Now we are ready to shoot the GPU.
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawArrays(GL_POINTS, 0, 6); // ignore the last 4 points which is for debug.

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    return 0;
}
