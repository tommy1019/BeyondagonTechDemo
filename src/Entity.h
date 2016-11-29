#ifndef ENTITY_H
#define ENTITY_H

#include <string>

#include "Shader.h"
#include "TessellationShader.h"
#include "Transform.h"
#include "SurfaceBall.h"

class Entity
{
    public:
        SurfaceBall surfaceBall;
        Transform transform;

        Entity(SurfaceBall surfaceBall, Transform transform = Transform());
        Entity(std::string surfaceFile, Transform transform = Transform());

        void render(TessellationShader shader, int resolution);
        void renderPoints(Shader shader);
};

#endif
