#include "SurfaceBall.h"

#include <fstream>
#include <vector>

#include <iostream>

#include <stdint.h>

SurfaceBall::SurfaceBall(std::string fileName, bool compressed)
{
    uint32_t numPatches;
    uint32_t numVertices;
    
    std::vector<GLuint> patches;
    std::vector<float> verticesTmp;
    
    if (!compressed)
    {
        std::ifstream in(fileName);

        in >> numPatches;

        for (int i = 0; i < numPatches; i++)
        {
            for (int j = 0; j < 16; j++)
            {
                GLuint curNum;

                in >> curNum;
            
                patches.push_back(curNum - 1);
            }
        }

        in >> numVertices;
        
        for (int i = 0; i < numVertices * 3; i++)
        {
            float a;
            in >> a;
            verticesTmp.push_back(a);
        }
    }
    else
    {
        std::ifstream in(fileName, std::ios::binary);
        
        in.read((char*) &numPatches, 4);
        in.read((char*) &numVertices, 4);
        
        for (int i = 0; i < numPatches; i++)
        {
            for (int j = 0; j < 16; j++)
            {
                GLuint curNum;
                
                in.read((char*) &curNum, 4);
                
                patches.push_back(curNum - 1);
            }
        }
        
        for (int i = 0; i < numVertices * 3; i++)
        {
            float a;
            
            in.read((char*) &a, 4);
            
            verticesTmp.push_back(a);
        }
    }
    
    this->numPatches = numPatches;
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vertices);
    glBindBuffer(GL_ARRAY_BUFFER, vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verticesTmp.size(), verticesTmp.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &indices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * patches.size(), patches.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    std::cout << "VertexLoc: " << this->vertices << " indices: " << indices << std::endl;
    std::cout << "Loaded model: " << fileName << " with " << numPatches << " patches and " << numVertices << " vertices." << std::endl;
}
