#include "Quaternion.h"

#include <math.h>

Quaternion::Quaternion()
{
    x = 0;
    y = 0;
    z = 0;
}

Quaternion::Quaternion(float x, float y, float z, float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

float Quaternion::length()
{
    return sqrt(x * x + y * y + z * z + w * w);
}

Quaternion Quaternion::normalized()
{
    float length = this->length();
    return Quaternion(x / length, y / length, z / length, w / length);
}

Quaternion Quaternion::conjugate()
{
    return Quaternion(-x, -y, -z, w);
}

Quaternion Quaternion::operator*(const Quaternion a)
{
    Quaternion c;
    
    c.x = this->w * a.x + this->x * a.w + this->y * a.z - this->z * a.y;
    c.y = this->w * a.y - this->x * a.z + this->y * a.w + this->z * a.x;
    c.z = this->w * a.z + this->x * a.y - this->y * a.x + this->z * a.w;
    c.w = this->w * a.w - this->x * a.x - this->y * a.y - this->z * a.z;
    
    return c;
}

Quaternion Quaternion::initRotation(Vector3 axis, float amt)
{
    float sinValue = sin(amt / 2);
    float cosValue = cos(amt / 2);
    
    return Quaternion(axis.x * sinValue, axis.y * sinValue, axis.z * sinValue, cosValue);
}

Vector3 Quaternion::getForward()
{
    return Vector3(2.0f * (x * z - w * y), 2.0f * (y * z + w * x), 1.0f - 2.0f * (x * x + y * y));
}

Vector3 Quaternion::getBack()
{
    return Vector3(-2.0f * (x * z - w * y), -2.0f * (y * z + w * x), -(1.0f - 2.0f * (x * x + y * y)));
}

Vector3 Quaternion::getUp()
{
    return Vector3(2.0f * (x * y + w * z), 1.0f - 2.0f * (x * x + z * z), 2.0f * (y * z - w * x));
}

Vector3 Quaternion::getDown()
{
    return Vector3(-2.0f * (x * y + w * z), -(1.0f - 2.0f * (x * x + z * z)), -2.0f * (y * z - w * x));
}

Vector3 Quaternion::getRight()
{
    return Vector3(1.0f - 2.0f * (y * y + z * z), 2.0f * (x * y - w * z), 2.0f * (x * z + w * y));
}

Vector3 Quaternion::getLeft()
{
    return Vector3(-(1.0f - 2.0f * (y * y + z * z)), -2.0f * (x * y - w * z), -2.0f * (x * z + w * y));
}
