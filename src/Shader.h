#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

#include <string>

class Shader
{
    GLuint shader;

    public:
        Shader(string name);
};

#endif
