#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vector3.h"
#include "Matrix4.h"

class Transform
{
    public:
        static Matrix4 projection;

        Vector3 translation;
        Vector3 rotation;
        Vector3 scale;

        Transform();

        Matrix4 getWorldMatrix();
        Matrix4 getTransformMatrix();
};

#endif
