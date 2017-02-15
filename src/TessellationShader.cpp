#include "TessellationShader.h"

#include <iostream>

TessellationShader::TessellationShader(std::string name)
: Shader(name, true)
{
    uResolution = glGetUniformLocation(program, "resolution"); 
    uNumPatches = glGetUniformLocation(program, "numPatches");

    uDrawSingle = glGetUniformLocation(program, "drawSingle");
    uCurPatch = glGetUniformLocation(program, "curPatch");

    std::cout << name << "  uResolution  : " << uResolution << std::endl;
    std::cout << name << "  uNumPatches  : " << uNumPatches << std::endl;
    std::cout << name << "  uDrawSingle  : " << uDrawSingle << std::endl;
    std::cout << name << "  uCurPatch    : " << uCurPatch << std::endl;
}

void TessellationShader::updateGlobals(bool drawSingle, int curPatch)
{
    glUniform1i(uDrawSingle, drawSingle);
    glUniform1i(uCurPatch, curPatch);   
}

void TessellationShader::updateResolution(int r)
{
    glUniform1i(uResolution, r);
}

void TessellationShader::updateNumPatches(int n)
{
    glUniform1i(uNumPatches, n);
}
