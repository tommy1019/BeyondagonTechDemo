#ifndef SURFACE_BALL_H
#define SURFACE_BALL_H

#define GL3_PROTOTYPES 1
#include <GL/glew.h>

#include <string>

class SurfaceBall
{
    public:
        int numPatches;

        GLuint vao;
        GLuint vertices;
        GLuint indices;

        SurfaceBall(std::string fileName, bool compressed);
};

#endif
