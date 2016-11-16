#include "SurfaceBall.h"

#include <fstream>
#include <vector>

#include <iostream>

SurfaceBall::SurfaceBall(std::string fileName)
{
    std::ifstream in(fileName);

    in >> numPatches;

    std::vector<GLuint> patches;

    for (int i = 0; i < numPatches; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            GLuint curNum;

            in >> curNum;
            
            patches.push_back(curNum - 1);
        }
    }

    int numVertices;
    in >> numVertices;

    std::vector<float> vertices;

    for (int i = 0; i < numVertices; i++)
    {
        float a;
        
        in >> a;
        vertices.push_back(a);

        in >> a;
        vertices.push_back(a);

        in >> a;
        vertices.push_back(a);
    }

    glGenBuffers(1, &this->vertices);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &indices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * patches.size(), patches.data(), GL_STATIC_DRAW);

    std::cout << "VertexLoc: " << this->vertices << " indices: " << indices << std::endl;
    std::cout << "Loaded model: " << fileName << " with " << numPatches << " patches and " << numVertices << " vertices." << std::endl;
}
