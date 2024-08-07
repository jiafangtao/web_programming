#ifndef JPROGRAM_H_
#define JPROGRAM_H_

#include <map>
#include <string>
#include <glad/glad.h>
#include "JCommon.h"

using namespace std;

/// <summary>
/// Encapsulates a base OpenGL program
/// </summary>
class JGeneralProgram
{
public:
    JGeneralProgram();
    virtual ~JGeneralProgram();

    /// <summary>
    /// Returns the backend program
    /// </summary>
    /// <returns></returns>
    GLint program();

    JGeneralProgram* getActiveProgram();
    void setShader(enum ShaderType, const string & shaderCode);
    string getShader(ShaderType st);
    void link();
    void use();

private:
    static JGeneralProgram* activeProgram;
    GLuint m_program;
    map<ShaderType, string> m_shaders;
};

#endif //JPROGRAM_H_
