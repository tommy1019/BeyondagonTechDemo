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
        
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, surfaceBall.vertices);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, surfaceBall.indices);
    glDrawElements(GL_PATCHES, surfaceBall.numPatches * 16, GL_UNSIGNED_INT, NULL);
    
    glDisableVertexAttribArray(0);
}

void Entity::renderPoints(Shader shader, Camera camera)
{
    glUseProgram(shader.program);
    
    Matrix4 transformMatrix = camera.getTransformMatrix() * transform.getTransformMatrix();
    Matrix4 projectionMatrix = Transform::getProjectionMatrix(transformMatrix);

    shader.updateTransformMatrix(transformMatrix);
    shader.updateProjectionMatrix(projectionMatrix);
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, surfaceBall.vertices);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, surfaceBall.indices);
    glDrawElements(GL_POINTS, surfaceBall.numPatches * 16, GL_UNSIGNED_INT, NULL);
    
    glDisableVertexAttribArray(0);
}
