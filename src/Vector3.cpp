#include "Vector3.h"

Vector3::Vector3()
{
    x = 0;
    y = 0;
    z = 0;
}

Vector3::Vector3(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3 Vector3::operator+(const Vector3 a)
{
    return Vector3( this->x + a.x,
                    this->y + a.y,
                    this->z + a.z);
}

Vector3 Vector3::operator-(const Vector3 a)
{
    return Vector3( this->x - a.x,
                    this->y - a.y,
                    this->z - a.z);
}

Vector3 Vector3::operator*(const float a)
{
    return Vector3( this->x * a,
                    this->y * a,
                    this->z * a);
}
