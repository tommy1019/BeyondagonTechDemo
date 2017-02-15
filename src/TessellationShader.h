#ifndef TESSELLATION_SHADER_H
#define TESSELLATION_SHADER_H

#include "Shader.h"

class TessellationShader : public Shader
{
    public:
        GLuint uResolution;
        GLuint uNumPatches;

        GLuint uDrawSingle;
        GLuint uCurPatch;

        TessellationShader(std::string name);

        void updateResolution(int r);
        void updateNumPatches(int n);

        void updateGlobals(bool drawSingle, int curPatch);
};

#endif
