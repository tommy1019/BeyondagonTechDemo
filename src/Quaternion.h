#ifndef QUATERNION_H
#define QUATERNION_H

#include "Vector3.h"

class Quaternion
{
public:
    float x, y, z, w;
    
    Quaternion();
    Quaternion(float x, float y, float z, float w);
    
    float length();
    Quaternion normalized();
    Quaternion conjugate();
    
    Quaternion operator*(const Quaternion a);
    
    Vector3 getForward();
    Vector3 getBack();
    Vector3 getUp();
    Vector3 getDown();
    Vector3 getLeft();
    Vector3 getRight();
    
    static Quaternion initRotation(Vector3 axis, float amt);
};

#endif
