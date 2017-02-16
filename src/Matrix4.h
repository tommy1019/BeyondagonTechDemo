#ifndef MATRIX4_H
#define MATRIX4_H

#include <math.h>

#include "Vector3.h"
#include "Quaternion.h"

struct Matrix4
{
public:
    float a[4][4];

    static Matrix4 initTranslation(Vector3 t);
    static Matrix4 initScale(Vector3 s);
    static Matrix4 initRotation(Vector3 r);
    static Matrix4 initRotation(Quaternion r);
    static Matrix4 initRotation(Vector3 f, Vector3 u, Vector3 r);
    static Matrix4 initProjection(float w, float h, float fov, float zNear, float zFar);

    Matrix4 operator*(const Matrix4 r);
};

#endif
