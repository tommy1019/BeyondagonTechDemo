#ifndef SURFACE_H
#define SURFACE_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>

#define GL3_PROTOTYPES 1
#include <GL/glew.h>

class Surface
{
public:
    GLuint vertexPtr;
    GLuint normalPtr;
    GLuint texturePtr;
    GLuint indicePtr;
    
    int numIndicies;
    
    Surface(std::string fileName);
};

#endif
