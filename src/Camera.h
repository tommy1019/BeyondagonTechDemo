#ifndef CAMERA_H
#define CAMERA_H

#include "Transform.h"

#include "Quaternion.h"

class Camera
{
public:    
    Vector3 translation;
    Quaternion rotation;
    
    Camera();
    
    Matrix4 getTransformMatrix();
};

#endif
