#include "JProgram.h"
#include "JError.h"

JGeneralProgram* JGeneralProgram::activeProgram = nullptr;

JGeneralProgram::JGeneralProgram() {
    m_program = GL_INVALID_INDEX;
}

JGeneralProgram::~JGeneralProgram() {
    //TODO: free resources
}

GLint JGeneralProgram::program() {
    return m_program;
}

void JGeneralProgram::setShader(ShaderType st, const string& shaderCode) {
    if (m_program == GL_INVALID_INDEX) {
        m_program = glCreateProgram();
    }

    if (m_program == GL_INVALID_INDEX) {
        throw new JError("Failed to create opengl program");
    }

    m_shaders[st] = shaderCode;

    GLenum shaderType;
    switch (st)
    {
    case ShaderType_Vertex:
        shaderType = GL_VERTEX_SHADER;
        break;
    case ShaderType_Fragment:
        shaderType = GL_FRAGMENT_SHADER;
        break;
    default:
        break;
    }

    const GLuint shader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar* data = shaderCode.c_str();
    glShaderSource(shader, 1, &data, NULL);
    glCompileShader(shader);

    glAttachShader(m_program, shader);

    //TODO: check gl error
}

string JGeneralProgram::getShader(ShaderType st) {
    return m_shaders[st];
}

void JGeneralProgram::link() {
    if (m_program == GL_INVALID_INDEX) {
        throw new JError("Invalid opengl program");
    }

    glLinkProgram(m_program);
}

void JGeneralProgram::use() {
    if (m_program == GL_INVALID_INDEX) {
        throw new JError("Invalid opengl program");
    }

    glUseProgram(m_program);
    activeProgram = this;
}

JGeneralProgram* JGeneralProgram::getActiveProgram() {
    return activeProgram;
}
