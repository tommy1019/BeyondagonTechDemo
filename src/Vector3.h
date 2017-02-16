#ifndef VECTOR3_H
#define VECTOR3_H

struct Vector3
{
    public:

        float x;
        float y;
        float z;

        Vector3();
        Vector3(float x, float y, float z);

        Vector3 operator+(const Vector3 a);
        Vector3 operator-(const Vector3 a);
    
        Vector3 operator*(const float a);
};

#endif
