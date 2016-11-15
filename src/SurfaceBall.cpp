#include "SurfaceBall.h"

#include <fstream>
#include <vector>

#include <iostream>

SurfaceBall::SurfaceBall(std::string fileName)
{
    std::ifstream in(fileName);

    in >> numPatches;

    std::vector<std::vector<int> > patches;

    for (int i = 0; i < numPatches; i++)
    {
        std::vector<int> curPatch;

        for (int j = 0; j < 16; j++)
        {
            int curNum;

            in >> curNum;
            
            curPatch.push_back(curNum);
            std::cout << curNum << ",";
        }

        std::cout << std::endl;

        patches.push_back(curPatch);
    }

    int numVertices;
    in >> numVertices;

    std::vector<double> vertices;

    for (int i = 0; i < numVertices; i++)
    {
        double a;
        
        in >> a;
        vertices.push_back(a);
std::cout << "[" << a;

        in >> a;
        vertices.push_back(a);
std::cout << "," << a;

        in >> a;
        vertices.push_back(a);
std::cout << "," << a << "]" << std::endl;

    }

    std::cout << "Loaded model: " << fileName << " with " << numPatches << " patches and " << numVertices << " vertices." << std::endl;
}
