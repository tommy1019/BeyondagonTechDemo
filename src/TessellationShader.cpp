#include "TessellationShader.h"

TessellationShader::TessellationShader(std::string name)
: Shader(name, true)
{
    uResolution = glGetUniformLocation(program, "resolution"); 
}

void TessellationShader::updateResolution(int r)
{
    glUniform1i(uResolution, r);
}
