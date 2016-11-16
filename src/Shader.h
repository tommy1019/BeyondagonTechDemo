#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

#include <string>

class Shader
{
    public:
        GLuint program;

        Shader(std::string name);
};

#endif
