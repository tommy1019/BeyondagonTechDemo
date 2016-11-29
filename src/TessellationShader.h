#ifndef TESSELLATION_SHADER_H
#define TESSELLATION_SHADER_H

#include "Shader.h"

class TessellationShader : public Shader
{
    public:
        GLuint uResolution;
        
        TessellationShader(std::string name);

        void updateResolution(int r);
};

#endif
