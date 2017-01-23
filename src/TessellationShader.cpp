#include "TessellationShader.h"

TessellationShader::TessellationShader(std::string name)
: Shader(name, true)
{
    uResolution = glGetUniformLocation(program, "resolution"); 
    uNumPatches = glGetUniformLocation(program, "numPatches");
}

void TessellationShader::updateResolution(int r)
{
    glUniform1i(uResolution, r);
}

void TessellationShader::updateNumPatches(int n)
{
    glUniform1i(uNumPatches, n);
}
