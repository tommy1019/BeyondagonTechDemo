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
        Transform(Vector3 translation, Vector3 rotation, Vector3 scale)
            :   translation(translation), rotation(rotation), scale(scale)
            {};

        Matrix4 getTransformMatrix();
        static Matrix4 getProjectionMatrix(Matrix4 transform);
};

#endif
