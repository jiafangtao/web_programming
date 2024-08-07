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

static Vertex vertices[6] =
{
    { { -0.6f, -0.4f }, { 1.f, 0.f, 0.f } },
    { {  0.6f, -0.4f }, { 0.f, 1.f, 0.f } },
    { {   0.f,  0.6f }, { 0.f, 0.f, 1.f } },
    { { 3-0.6f, 0.6f }, { 0.f, 0.f, 1.f } },
    { {  3.6f, 0.6f }, { 0.f, 1.f, 0.f } },
    { {  3.f,  -0.4f }, { 1.f, 0.f, 0.f } }
};

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

static float g_pt_size = 1.0f;
static GLint ptSize_location = GL_INVALID_INDEX ;

static float g_zoom_factor = 1.0f;
static GLint zoomFactor_location = GL_INVALID_INDEX;

static float g_color_factor = 1.0f;
static GLint colorFactor_location = GL_INVALID_INDEX;

// flags to control the behavior
static bool g_flag_rotating = false;
static bool g_flag_animate_colors = true;

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
            cout << "make point bigger" << endl;
        }
        else
        {
            cout << "point is big enough:" << g_pt_size << endl;
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
            cout << "make point smaller" << endl;
        }
        else
        {
            cout << "point is small enough: " << g_pt_size << endl;
        }
        
        g_pt_size -= 1.0f;

        if (g_pt_size < 1.0f) {
            g_pt_size = 1.0f;
        }
        glUniform1f(ptSize_location, g_pt_size);
    }
    else if ((key == GLFW_KEY_7 || key == GLFW_KEY_F7) && action == GLFW_PRESS)
    {
        cout << "Key F7 (or 7): zoom in" << endl;
        g_zoom_factor *= 2.0f;
        glUniform1f(zoomFactor_location, g_zoom_factor);
    }
    else if ((key == GLFW_KEY_8 || key == GLFW_KEY_F8) && action == GLFW_PRESS)
    {
        cout << "Key F8 (or 8): zoom out" << endl;
        g_zoom_factor /= 2.0f;
        glUniform1f(zoomFactor_location, g_zoom_factor);
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

// GLFWframebuffersizefun
void resize_callback(GLFWwindow* window, int width, int height)
{
    if (window == nullptr) 
        return;
    if (glfwGetCurrentContext() != window) 
        return;

    glViewport(0, 0, width, height);
}

// forward declarations
void showRenderMode();

void showFeedbackBuffer(GLfloat* buffer, GLsizei cnt);


int main(int argc, char** argv)
{
    Initializer glfw;

    glfwSetErrorCallback(error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    
    //NOTE: this requires OpenGL 4.3 or a debug extension. And this will heavily slow down the app.
    //glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true); // enable debug for gl

    GLFWwindow* window = glfwCreateWindow(640, 480, "Demo - Triangles", NULL, NULL);
    if (!window)
    {
        // Window or OpenGL context creation failed
        return 2;
    }

    //TODO: fill it soon ...
    //JGeneralProgram background; 

    /*
    
    
    JGeneralProgram twoTriangles;
    twoTriangles.setShader(ShaderType_Vertex, vertex_shader_text);
    twoTriangles.setShader(ShaderType_Fragment, fragment_shader_text);
    twoTriangles.link();
    twoTriangles.use();

    GLint program = twoTriangles.program();
    */

    glfwSetKeyCallback(window, key_callback);

    // Make the OpenGL context current. This is important and most be called after load GL (via glad or alternatives)
    glfwMakeContextCurrent(window);

    // Load all OpenGL functions using the glfw loader function
    // If you use SDL you can use: https://wiki.libsdl.org/SDL_GL_GetProcAddress
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }

    // Alternative use the builtin loader, e.g. if no other loader function is available
    /*
    if (!gladLoadGL()) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }
    */

    // glad populates global constants after loading to indicate,
    // if a certain extension/version is available.
    printf("OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);

    if (GLAD_GL_VERSION_3_0) {
        /* We support at least OpenGL version 3 */
    }

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

    // A block to play with texture. (test purpose only)
    {
        GLuint textA;
        glGenTextures(1, &textA);

        glBindTexture(GL_TEXTURE_2D, textA);

        // unbind texture from the unit.
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    const GLint mvp_location = glGetUniformLocation(program, "MVP");
    const GLint vpos_location = glGetAttribLocation(program, "vPos");
    const GLint vcol_location = glGetAttribLocation(program, "vCol");

    ptSize_location = glGetUniformLocation(program, "ptSize");
    zoomFactor_location = glGetUniformLocation(program, "zoomFactor");
    colorFactor_location = glGetUniformLocation(program, "colorFactor");

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

    //NOTE: play with feedback mode
    GLsizei size = 512;
    GLenum typ = GL_3D;
    GLfloat* buffer = new GLfloat[size];
    memset(buffer, 0, sizeof(buffer[0]) * size);


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
            //NOTE: I don't know if rotate really change model matrix. should it?
            //
            mat4x4_rotate_Z(m, m, (float)glfwGetTime());
        }

        if (g_flag_animate_colors) {
            g_color_factor = abs((float)sin(glfwGetTime()));
        }

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


        // this section is for feedback mode
        if (0) {
            //sanity check - 
            //  calling glFeedbackBuffer while the GL is in feedback mode, GL will raise an error. 
            GLint renderMode = 0;
            glGetIntegerv(GL_RENDER_MODE, &renderMode);

            if (renderMode != GL_FEEDBACK) {
                glFeedbackBuffer(size, typ, buffer);
                checkError(__FILE__, __LINE__);

                GLint cnt = glRenderMode(GL_FEEDBACK);
                std::cout << "glRenderMode returns " << cnt << std::endl;

                checkError(__FILE__, __LINE__);
            }
        }
        
        // Now we are ready to shoot the GPU.
        glDrawArrays(GL_POINTS, 0, 6);
        checkError(__FILE__, __LINE__);

        // triangle #1 - keep original color
        glUniform1f(colorFactor_location, 1);
        checkError(__FILE__, __LINE__);

        //glDrawArrays(GL_TRIANGLES, 0, 3);
        //checkError(__FILE__, __LINE__);

        // triangle #2 - animate the color
        //glRenderMode(GL_RENDER);
        checkError(__FILE__, __LINE__);

        glUniform1f(colorFactor_location, g_color_factor);
        checkError(__FILE__, __LINE__);

        glDrawArrays(GL_TRIANGLES, 3, 3);
        checkError(__FILE__, __LINE__);

        GLsizei cnt = glRenderMode(GL_FEEDBACK); // it returns count of entries
        std::cout << "glRenderMode returns " << cnt << std::endl;

        showFeedbackBuffer(buffer, cnt);

        glfwSwapBuffers(window);
        glfwPollEvents();
    } //end of loop
    
    glfwDestroyWindow(window);
    return 0;
}

void showRenderMode() {
    GLint renderMode = 0;
    glGetIntegerv(GL_RENDER_MODE, &renderMode);

    std::cout << "current mode is ";
    switch (renderMode)
    {
    case GL_RENDER:
        std::cout << "GL_RENDER" << std::endl;
        break;
    case GL_SELECT:
        std::cout << "GL_SELECT" << std::endl;
        break;
    case GL_FEEDBACK:
        std::cout << "GL_FEEDBACK" << std::endl;
        break;
    default:
        std::cout << "oops!" << std::endl;
        break;
    }
}

void showFeedbackBuffer(GLfloat* buffer, GLsizei cnt) {
    GLsizei idx = 0;
    while (idx < cnt) {
        GLfloat token = buffer[idx];
        if (token == GL_POINT_TOKEN) {
            //
            float x = buffer[idx + 1];
            float y = buffer[idx + 2];
            float z = buffer[idx + 3];
            std::cout << "point(" << x << ", " << y << ", " << z << ")" << std::endl;

            idx += /*token*/ 1 + /*x,y,z*/ 3;
        }
        else if (token == GL_LINE_TOKEN) {
            std::cout << "GL_LINE_TOKEN" << std::endl;
            // how many points are in the line?
            int nPoints = (int)buffer[idx + 1];
            for (int i = 0; i < nPoints; i++) {
                float x = buffer[idx + 2 + i*3];
                float y = buffer[idx + 3 + i * 3];
                float z = buffer[idx + 4 + i * 3];

                std::cout << "point(" << x << ", " << y << ", " << z << ")" << std::endl;
            }

            idx += /*token*/ 1 + /*line length*/ 1 + 3 * nPoints;
        }
        else if (token == GL_LINE_RESET_TOKEN) {
            std::cout << " GL_LINE_RESET_TOKEN" << std::endl;
        }
        else if (token == GL_POLYGON_TOKEN) {
            std::cout << "polygon(";
            float n = buffer[idx+1];
            // process n vertex
            for (int j = 0; j < n; j++) {
                float x = buffer[idx + 2 + j * 3];
                float y = buffer[idx + 2 + j * 3 + 1];
                float z = buffer[idx + 2 + j * 3 + 2];

                std::cout << x << ", " << y << ", " << z << "; ";
            }
            
            std::cout << ")" << std::endl;
            idx += /*token*/ 1 + /*size*/ 1 + /* n*(x,y,z) */ n * 3;
        }
        else if (token == GL_BITMAP_TOKEN) {
            std::cout << "GL_BITMAP_TOKEN " << std::endl;
        }
        else if (token == GL_DRAW_PIXEL_TOKEN) {
            std::cout << "GL_DRAW_PIXEL_TOKEN " << std::endl;
        }
        else if (token == GL_COPY_PIXEL_TOKEN) {
            std::cout << "GL_COPY_PIXEL_TOKEN " << std::endl;
        }
        else if (token == GL_PASS_THROUGH_TOKEN) {
            std::cout << "GL_PASS_THROUGH_TOKEN " << std::endl;
        }
        else {
            std::cout << "unsupported token type yet" << std::endl;
            idx += 1;
        }
    }
}