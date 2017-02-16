#ifndef ENTITY_H
#define ENTITY_H

#include <string>

#include "Shader.h"
#include "TessellationShader.h"
#include "Transform.h"
#include "SurfaceBall.h"
#include "Camera.h"

class Entity
{
    public:
        SurfaceBall surfaceBall;
        Transform transform;

        Entity(SurfaceBall surfaceBall, Transform transform = Transform());
        Entity(std::string surfaceFile, Transform transform = Transform());

        void render(TessellationShader shader, int resolution, Camera camera);
        void renderPoints(Shader shader, Camera camera);
};

#endif
