#include "Shader.h"

#include <iostream>
#include <fstream>
#include <streambuf>

GLuint loadShader(std::string name, GLuint shaderType);
std::string loadFile(std::string name);

Shader::Shader(std::string name, bool loadTes)
{
    program = glCreateProgram();
    
    GLuint vertexShader                 = loadShader(name + ".vs",  GL_VERTEX_SHADER);
    GLuint fragmentShader               = loadShader(name + ".fs",  GL_FRAGMENT_SHADER);
 
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    if (loadTes)
    {
        GLuint tessellationControlShader    = loadShader(name + ".tcs", GL_TESS_CONTROL_SHADER);
        GLuint tessellationEvalShader       = loadShader(name + ".tes", GL_TESS_EVALUATION_SHADER);

        glAttachShader(program, tessellationControlShader);
        glAttachShader(program, tessellationEvalShader);
        
        glDeleteShader(tessellationControlShader);
        glDeleteShader(tessellationEvalShader);
    }

    glLinkProgram(program);

    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success)
    {
        GLchar infoLog[512];
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "Error: Linking shader\n" << infoLog << std::endl;
    }

    glBindAttribLocation(program, positionPos, "position");

    uTransformMatrix = glGetUniformLocation(program, "transform");
    uProjectionMatrix = glGetUniformLocation(program, "projection");

    std::cout << name << "  uTransform   : " << uTransformMatrix << std::endl;
    std::cout << name << "  uProjection  : " << uProjectionMatrix << std::endl;
}

void Shader::updateTransformMatrix(Matrix4 a)
{
    glUniformMatrix4fv(uTransformMatrix, 1, false, &a.a[0][0]);
}

void Shader::updateProjectionMatrix(Matrix4 a)
{
    glUniformMatrix4fv(uProjectionMatrix, 1, false, &a.a[0][0]);
}

std::string loadFile(std::string name)
{
    std::string content;
    std::ifstream fileStream(name, std::ios::in);
    
    if(!fileStream.is_open()) 
    {
        std::cerr << "Error: Reading file" << std::endl;
        return "";
    }

    std::string line = "";
    while(!fileStream.eof())
    {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}


GLuint loadShader(std::string name, GLuint shaderType)
{
    GLuint shader;
    shader = glCreateShader(shaderType);    

    std::string shaderSource = loadFile(name);
    const char *c_str = shaderSource.c_str();

    glShaderSource(shader, 1, &c_str, NULL);
    glCompileShader(shader);

    GLint success;
    GLchar infoLog[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "Error: " << name << " shader failed to compile\n" << infoLog << std::endl;        
        return 0;
    }

    return shader;
}
