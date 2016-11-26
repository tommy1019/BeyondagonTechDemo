#include "Matrix4.h"

Matrix4 Matrix4::initTranslation(float x, float y, float z)
{
    a[0][0] = 1; a[0][1] = 0; a[0][2] = 0; a[0][3] = x;
    a[1][0] = 0; a[1][1] = 1; a[1][2] = 0; a[1][3] = y;
    a[2][0] = 0; a[2][1] = 0; a[2][2] = 1; a[2][3] = z;
    a[3][0] = 0; a[3][1] = 0; a[3][2] = 0; a[3][3] = 1;

    return *this;
}

Matrix4 Matrix4::initScale(float x, float y, float z)
{
    a[0][0] = x; a[0][1] = 0; a[0][2] = 0; a[0][3] = 0;
    a[1][0] = 0; a[1][1] = y; a[1][2] = 0; a[1][3] = 0;
    a[2][0] = 0; a[2][1] = 0; a[2][2] = z; a[2][3] = 0;
    a[3][0] = 0; a[3][1] = 0; a[3][2] = 0; a[3][3] = 1;

    return *this;
}
    
Matrix4 Matrix4::initRotation(float x, float y, float z)
{
    Matrix4 rx;
    Matrix4 ry;
    Matrix4 rz;

    rx.a[0][0] = 1; rx.a[0][1] = 0;         rx.a[0][2] = 0;         rx.a[0][3] = 0;
    rx.a[1][0] = 0; rx.a[1][1] = cos(x);    rx.a[1][2] = -sin(x);   rx.a[1][3] = 0;
    rx.a[2][0] = 0; rx.a[2][1] = sin(x);    rx.a[2][2] = cos(x);    rx.a[2][3] = 0;
    rx.a[3][0] = 0; rx.a[3][1] = 0;         rx.a[3][2] = 0;         rx.a[3][3] = 1;
    
    ry.a[0][0] = cos(y);    ry.a[0][1] = 0; ry.a[0][2] = sin(y);    ry.a[0][3] = 0;
    ry.a[1][0] = 0;         ry.a[1][1] = 1; ry.a[1][2] = 0;         ry.a[1][3] = 0;
    ry.a[2][0] = -sin(y);   ry.a[2][1] = 0; ry.a[2][2] = cos(y);    ry.a[2][3] = 0;
    ry.a[3][0] = 0;         ry.a[3][1] = 0; ry.a[3][2] = 0;         ry.a[3][3] = 1;
        
    rz.a[0][0] = cos(z);    rz.a[0][1] = -sin(z);   rz.a[0][2] = 0; rz.a[0][3] = 0;
    rz.a[1][0] = sin(z);    rz.a[1][1] = cos(z);    rz.a[1][2] = 0; rz.a[1][3] = 0;
    rz.a[2][0] = 0;         rz.a[2][1] = 0;         rz.a[2][2] = 1; rz.a[2][3] = 0;
    rz.a[3][0] = 0;         rz.a[3][1] = 0;         rz.a[3][2] = 0; rz.a[3][3] = 1;

    return rx * ry * rz;
}

Matrix4 Matrix4::initProjection(float w, float h, float fov, float zNear, float zFar)
{
    float asp = w / h;
    float f = 1 / tan(fov / 2);

    a[0][0] = f / asp;      a[0][1] = 0;    a[0][2] = 0;                                a[0][3] = 0;
    a[1][0] = 0;            a[1][1] = f;    a[1][2] = 0;                                a[1][3] = 0;
    a[2][0] = 0;            a[2][1] = 0;    a[2][2] = (zFar + zNear) / (zNear - zFar);  a[2][3] = (2 * zFar * zNear) / (zNear - zFar);
    a[3][0] = 0;            a[3][1] = 0;    a[3][2] = -1;                               a[3][3] = 0;

    return *this;
}

Matrix4 Matrix4::operator*(const Matrix4 r)
{
    Matrix4 l = *this;
    Matrix4 res;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            res.a[i][j] = 0;
            for (int k = 0; k < 4; k++)
            {
                res.a[i][j] += l.a[i][k] * r.a[k][j];
            }
        }

    return res;
}
