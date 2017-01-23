#include "Entity.h"

Entity::Entity(SurfaceBall surfaceBall, Transform transform)
:   surfaceBall(surfaceBall),
    transform(transform)
{
}

Entity::Entity(std::string surfaceFile, Transform transform)
:   surfaceBall(surfaceFile),
    transform(transform)
{
}

void Entity::render(TessellationShader shader, int resolution)
{
    glUseProgram(shader.program);
    shader.updateProjectionMatrix(transform.getTransformMatrix());
    shader.updateResolution(resolution);
    shader.updateNumPatches(surfaceBall.numPatches);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, surfaceBall.indices);
    glDrawElements(GL_PATCHES, surfaceBall.numPatches * 16, GL_UNSIGNED_INT, NULL);
}

void Entity::renderPoints(Shader shader)
{
    glUseProgram(shader.program);
    shader.updateProjectionMatrix(transform.getTransformMatrix());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, surfaceBall.indices);
    glDrawElements(GL_POINTS, surfaceBall.numPatches * 16, GL_UNSIGNED_INT, NULL);
}
