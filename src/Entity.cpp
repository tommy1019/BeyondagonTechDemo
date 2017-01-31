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

    Matrix4 transformMatrix = transform.getTransformMatrix();

    shader.updateTransformMatrix(transformMatrix);
    shader.updateProjectionMatrix(Transform::getProjectionMatrix(transformMatrix));
    shader.updateResolution(resolution);
    shader.updateNumPatches(surfaceBall.numPatches);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, surfaceBall.indices);
    glDrawElements(GL_PATCHES, surfaceBall.numPatches * 16, GL_UNSIGNED_INT, NULL);
}

void Entity::renderPoints(Shader shader)
{
    glUseProgram(shader.program);
    
    Matrix4 transformMatrix = transform.getTransformMatrix();

    shader.updateTransformMatrix(transformMatrix);
    shader.updateProjectionMatrix(Transform::getProjectionMatrix(transformMatrix));
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, surfaceBall.indices);
    glDrawElements(GL_POINTS, surfaceBall.numPatches * 16, GL_UNSIGNED_INT, NULL);
}
