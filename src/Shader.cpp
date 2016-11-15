#include "Shader.h"

string loadFile(string name);

Shader::Shader(string name)
{
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
}
