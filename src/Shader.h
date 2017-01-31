#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

#include <string>

#include "Matrix4.h"

class Shader
{
    public:
        GLuint uTransformMatrix;
        GLuint uProjectionMatrix;

        GLuint program;
        GLuint positionPos;

        Shader(std::string name, bool loadTes);

        void updateTransformMatrix(Matrix4 a);
        void updateProjectionMatrix(Matrix4 a);
};

#endif
