#include "Matrix4.h"

Matrix4 Matrix4::initTranslation(Vector3 t)
{
    Matrix4 res;

    res.a[0][0] = 1; res.a[0][1] = 0; res.a[0][2] = 0; res.a[0][3] = t.x;
    res.a[1][0] = 0; res.a[1][1] = 1; res.a[1][2] = 0; res.a[1][3] = t.y;
    res.a[2][0] = 0; res.a[2][1] = 0; res.a[2][2] = 1; res.a[2][3] = t.z;
    res.a[3][0] = 0; res.a[3][1] = 0; res.a[3][2] = 0; res.a[3][3] = 1;

    return res;
}

Matrix4 Matrix4::initScale(Vector3 s)
{
    Matrix4 res;

    res.a[0][0] = s.x;  res.a[0][1] = 0;    res.a[0][2] = 0;    res.a[0][3] = 0;
    res.a[1][0] = 0;    res.a[1][1] = s.y;  res.a[1][2] = 0;    res.a[1][3] = 0;
    res.a[2][0] = 0;    res.a[2][1] = 0;    res.a[2][2] = s.z;  res.a[2][3] = 0;
    res.a[3][0] = 0;    res.a[3][1] = 0;    res.a[3][2] = 0;    res.a[3][3] = 1;

    return res;
}
    
Matrix4 Matrix4::initRotation(Vector3 r)
{
    Matrix4 rx;
    Matrix4 ry;
    Matrix4 rz;

    rx.a[0][0] = 1; rx.a[0][1] = 0;         rx.a[0][2] = 0;         rx.a[0][3] = 0;
    rx.a[1][0] = 0; rx.a[1][1] = cos(r.x);  rx.a[1][2] = -sin(r.x); rx.a[1][3] = 0;
    rx.a[2][0] = 0; rx.a[2][1] = sin(r.x);  rx.a[2][2] = cos(r.x);  rx.a[2][3] = 0;
    rx.a[3][0] = 0; rx.a[3][1] = 0;         rx.a[3][2] = 0;         rx.a[3][3] = 1;
    
    ry.a[0][0] = cos(r.y);  ry.a[0][1] = 0; ry.a[0][2] = sin(r.y);  ry.a[0][3] = 0;
    ry.a[1][0] = 0;         ry.a[1][1] = 1; ry.a[1][2] = 0;         ry.a[1][3] = 0;
    ry.a[2][0] = -sin(r.y); ry.a[2][1] = 0; ry.a[2][2] = cos(r.y);  ry.a[2][3] = 0;
    ry.a[3][0] = 0;         ry.a[3][1] = 0; ry.a[3][2] = 0;         ry.a[3][3] = 1;
        
    rz.a[0][0] = cos(r.z);  rz.a[0][1] = -sin(r.z); rz.a[0][2] = 0; rz.a[0][3] = 0;
    rz.a[1][0] = sin(r.z);  rz.a[1][1] = cos(r.z);  rz.a[1][2] = 0; rz.a[1][3] = 0;
    rz.a[2][0] = 0;         rz.a[2][1] = 0;         rz.a[2][2] = 1; rz.a[2][3] = 0;
    rz.a[3][0] = 0;         rz.a[3][1] = 0;         rz.a[3][2] = 0; rz.a[3][3] = 1;

    return rx * ry * rz;
}

Matrix4 Matrix4::initProjection(float w, float h, float fov, float zNear, float zFar)
{
    Matrix4 res;
    
    float asp = w / h;
    float f = 1 / tan(fov / 2);

    res.a[0][0] = f / asp;      res.a[0][1] = 0;    res.a[0][2] = 0;                                res.a[0][3] = 0;
    res.a[1][0] = 0;            res.a[1][1] = f;    res.a[1][2] = 0;                                res.a[1][3] = 0;
    res.a[2][0] = 0;            res.a[2][1] = 0;    res.a[2][2] = (zFar + zNear) / (zNear - zFar);  res.a[2][3] = (2 * zFar * zNear) / (zNear - zFar);
    res.a[3][0] = 0;            res.a[3][1] = 0;    res.a[3][2] = -1;                               res.a[3][3] = 0;

    return res;
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
