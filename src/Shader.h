#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

#include <string>

class Shader
{
    public:
        GLuint program;
        GLuint positionPos;

        Shader(std::string name, bool loadTes);
};

#endif
