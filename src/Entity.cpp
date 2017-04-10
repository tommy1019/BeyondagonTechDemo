#include "Entity.h"

Entity::Entity(SurfaceBall surfaceBall, Transform transform)
:   surfaceBall(surfaceBall),
    transform(transform)
{
}

Entity::Entity(std::string surfaceFile, bool compressed, Transform transform)
:   surfaceBall(surfaceFile, compressed),
    transform(transform)
{
}

void Entity::render(TessellationShader shader, int resolution, Camera camera)
{
    glUseProgram(shader.program);

    Matrix4 transformMatrix = transform.getTransformMatrix();
    Matrix4 projectionMatrix = Transform::projection * camera.getTransformMatrix() * transformMatrix;

    shader.updateTransformMatrix(transformMatrix);
    shader.updateProjectionMatrix(projectionMatrix);

    shader.updateResolution(resolution);
    shader.updateNumPatches(surfaceBall.numPatches);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, surfaceBall.indices);
    glDrawElements(GL_PATCHES, surfaceBall.numPatches * 16, GL_UNSIGNED_INT, NULL);
}

void Entity::renderPoints(Shader shader, Camera camera)
{
    glUseProgram(shader.program);
    
    Matrix4 transformMatrix = camera.getTransformMatrix() * transform.getTransformMatrix();
    Matrix4 projectionMatrix = Transform::getProjectionMatrix(transformMatrix);

    shader.updateTransformMatrix(transformMatrix);
    shader.updateProjectionMatrix(projectionMatrix);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, surfaceBall.indices);
    glDrawElements(GL_POINTS, surfaceBall.numPatches * 16, GL_UNSIGNED_INT, NULL);
}
