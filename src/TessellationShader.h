#ifndef TESSELLATION_SHADER_H
#define TESSELLATION_SHADER_H

#include "Shader.h"

class TessellationShader : public Shader
{
    public:
        GLuint uResolution;
        GLuint uNumPatches;

        GLuint uDrawSingle;
        GLuint uSelectedPatch;
    
        GLuint uEyePos;

        TessellationShader(std::string name);

        void updateResolution(int r);
        void updateNumPatches(int n);

        void updateGlobals(bool drawSingle, int selectedPatch);
    
        void updateEyePos(Vector3 e);
};

#endif
