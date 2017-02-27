#include "TessellationShader.h"

#include <iostream>

TessellationShader::TessellationShader(std::string name)
: Shader(name, true)
{
    uResolution = glGetUniformLocation(program, "resolution"); 
    uNumPatches = glGetUniformLocation(program, "numPatches");

    uDrawSingle = glGetUniformLocation(program, "drawSingle");
    uSelectedPatch = glGetUniformLocation(program, "selectedPatch");
    
    uEyePos = glGetUniformLocation(program, "eyePos");

    std::cout << name << "  uResolution  : " << uResolution << std::endl;
    std::cout << name << "  uNumPatches  : " << uNumPatches << std::endl;
    std::cout << name << "  uDrawSingle  : " << uDrawSingle << std::endl;
    std::cout << name << "  uSelePatch   : " << uSelectedPatch << std::endl;
    std::cout << name << "  uEyePos      : " << uEyePos << std::endl;
}

void TessellationShader::updateGlobals(bool drawSingle, int selectedPatch)
{
    glUniform1i(uDrawSingle, drawSingle);
    glUniform1i(uSelectedPatch, selectedPatch);
}

void TessellationShader::updateResolution(int r)
{
    glUniform1i(uResolution, r);
}

void TessellationShader::updateNumPatches(int n)
{
    glUniform1i(uNumPatches, n);
}

void TessellationShader::updateEyePos(Vector3 e)
{
    glUniform3f(uEyePos, e.x, e.y, e.z);
}
