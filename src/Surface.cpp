#include "Surface.h"

struct Vertex
{
    GLfloat x, y, z;
    GLfloat nx, ny, nz;
    GLfloat tx, ty;
    
    bool operator<(const Vertex& a) const
    {
        if (x != a.x) return x < a.x;
        if (y != a.y) return y < a.y;
        if (z != a.z) return z < a.z;
        
        if (x != a.x) return x < a.x;
        if (y != a.y) return y < a.y;
        if (z != a.z) return z < a.z;
        
        if (x != a.x) return x < a.x;
        if (y != a.y) return y < a.y;
        
        return true;
    };
};

Surface::Surface(std::string fileName)
{
    std::ifstream file("res/" + fileName);
    
    if (!file)
    {
        printf("Error loading file: %s\n", std::string("res/").append(fileName).c_str());
        throw 1;
    }
    
    std::vector<GLfloat> verticeTemp;
    std::vector<GLfloat> normalTemp;
    std::vector<GLfloat> textureTemp;
    
    std::vector<GLfloat> verticies;
    std::vector<GLfloat> normals;
    std::vector<GLfloat> textures;
    
    std::vector<GLuint> indicies;
    
    std::vector<Vertex> vertexes;
    std::map<Vertex, int> vertexMap;
    
    std::string curLine;
    while (getline(file, curLine))
    {
        if (curLine.substr(0, 2) == "v ")
        {
            std::istringstream s(curLine.substr(2));
            GLfloat v;
            
            s >> v;
            verticeTemp.push_back(v);
            
            s >> v;
            verticeTemp.push_back(v);
            
            s >> v;
            verticeTemp.push_back(v);
        }
        if (curLine.substr(0, 2) == "vn")
        {
            std::istringstream s(curLine.substr(2));
            GLfloat v;
            
            s >> v;
            normalTemp.push_back(v);
            
            s >> v;
            normalTemp.push_back(v);
            
            s >> v;
            normalTemp.push_back(v);
        }
        if (curLine.substr(0, 2) == "vt")
        {
            std::istringstream s(curLine.substr(2));
            GLfloat v;
            
            s >> v;
            textureTemp.push_back(v);
            
            s >> v;
            textureTemp.push_back(v);
        }
        if (curLine.substr(0, 2) == "f ")
        {
            GLuint pA, pB, pC;
            GLuint nA, nB, nC;
            GLuint tA, tB, tC;
            
            sscanf(curLine.substr(2).c_str(), "%i/%i/%i %i/%i/%i %i/%i/%i", &pA, &tA, &nA, &pB, &tB, &nB, &pC, &tC, &nC);
            
            Vertex a;
            a.x = verticeTemp[(pA - 1) * 3];
            a.y = verticeTemp[(pA - 1) * 3 + 1];
            a.z = verticeTemp[(pA - 1) * 3 + 2];
            
            a.nx = normalTemp[(nA - 1) * 3];
            a.ny = normalTemp[(nA - 1) * 3 + 1];
            a.nz = normalTemp[(nA - 1) * 3 + 2];
            
            a.tx = textureTemp[(tA - 1) * 2];
            a.ty = textureTemp[(tA - 1) * 2 + 1];
            
            Vertex b;
            b.x = verticeTemp[(pB - 1) * 3];
            b.y = verticeTemp[(pB - 1) * 3 + 1];
            b.z = verticeTemp[(pB - 1) * 3 + 2];
            
            b.nx = normalTemp[(nB - 1) * 3];
            b.ny = normalTemp[(nB - 1) * 3 + 1];
            b.nz = normalTemp[(nB - 1) * 3 + 2];
            
            b.tx = textureTemp[(tB - 1) * 2];
            b.ty = textureTemp[(tB - 1) * 2 + 1];
            
            Vertex c;
            c.x = verticeTemp[(pC - 1) * 3];
            c.y = verticeTemp[(pC - 1) * 3 + 1];
            c.z = verticeTemp[(pC - 1) * 3 + 2];
            
            c.nx = normalTemp[(nC - 1) * 3];
            c.ny = normalTemp[(nC - 1) * 3 + 1];
            c.nz = normalTemp[(nC - 1) * 3 + 2];
            
            c.tx = textureTemp[(tC - 1) * 2];
            c.ty = textureTemp[(tC - 1) * 2 + 1];
            
            if (vertexMap.find(a) == vertexMap.end())
            {
                vertexMap[a] = vertexes.size();
                indicies.push_back(vertexes.size());
                vertexes.push_back(a);
            }
            else
            {
                indicies.push_back(vertexMap[a]);
            }
            
            if (vertexMap.find(b) == vertexMap.end())
            {
                vertexMap[b] = vertexes.size();
                indicies.push_back(vertexes.size());
                vertexes.push_back(b);
            }
            else
            {
                indicies.push_back(vertexMap[b]);
            }
            
            if (vertexMap.find(c) == vertexMap.end())
            {
                vertexMap[c] = vertexes.size();
                indicies.push_back(vertexes.size());
                vertexes.push_back(c);
            }
            else
            {
                indicies.push_back(vertexMap[c]);
            }
            
        }
    }
    
    numIndicies = indicies.size();

    std::cout << "Loaded normal model with " << numIndicies << " indicies, " << (verticeTemp.size() / 3) << " verticies, " << (normalTemp.size() / 3)  << " normals, " << (textureTemp.size() / 2) << " texture coords" << std::endl;

    for(uint i = 0; i < vertexes.size(); i++)
    {
        Vertex v = vertexes[i];
        verticies.push_back(v.x);
        verticies.push_back(v.y);
        verticies.push_back(v.z);
        normals.push_back(v.nx);
        normals.push_back(v.ny);
        normals.push_back(v.nz);
        textures.push_back(v.tx);
        textures.push_back(v.ty);
    }
    
    glGenBuffers(1, &vertexPtr);
    glBindBuffer(GL_ARRAY_BUFFER, vertexPtr);
    glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(float), verticies.data(), GL_STATIC_DRAW);
    
    glGenBuffers(1, &normalPtr);
    glBindBuffer(GL_ARRAY_BUFFER, normalPtr);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STATIC_DRAW);
    
    glGenBuffers(1, &texturePtr);
    glBindBuffer(GL_ARRAY_BUFFER, texturePtr);
    glBufferData(GL_ARRAY_BUFFER, textures.size() * sizeof(float), textures.data(), GL_STATIC_DRAW);
    
    glGenBuffers(1, &indicePtr);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicePtr);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndicies * sizeof(GLuint), indicies.data(), GL_STATIC_DRAW);
}
