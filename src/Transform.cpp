#include "Transform.h"

Matrix4 Transform::projection;

Transform::Transform()
{
    translation = Vector3(0, 0, 0);
    rotation = Vector3(0, 0, 0);
    scale = Vector3(1, 1, 1);
}

Matrix4 Transform::getTransformMatrix()
{
    Matrix4 translation = Matrix4::initTranslation(this->translation);
    Matrix4 rotation = Matrix4::initRotation(this->rotation);
    Matrix4 scale = Matrix4::initScale(this->scale);

    return translation * rotation * scale;
}

Matrix4 Transform::getProjectionMatrix(Matrix4 transform)
{
    return transform * Transform::projection;
}
