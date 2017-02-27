#include "Camera.h"

Camera::Camera()
{
    translation = Vector3(0, 0, 0);
    rotation = Quaternion(0, 0, 0, 1);
}

Matrix4 Camera::getTransformMatrix()
{
    Matrix4 transl = Matrix4::initTranslation(Vector3(-this->translation.x, -this->translation.y, -this->translation.z));
    Matrix4 rot = Matrix4::initRotation(this->rotation);
    
    return rot * transl;
}
