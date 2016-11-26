#ifndef MATRIX4_H
#define MATRIX4_H

#include <math.h>

struct Matrix4
{
public:
    float a[4][4];

    Matrix4 initTranslation(float x, float y, float z);
    Matrix4 initScale(float x, float y, float z);
    Matrix4 initRotation(float x, float y, float z);
    Matrix4 initProjection(float w, float h, float fov, float zNear, float zFar);

    Matrix4 operator*(const Matrix4 r);
};

#endif
