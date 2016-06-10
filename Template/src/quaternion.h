#ifndef QUATERNION_H
#define QUATERNION_H

#include<math.h>
#include"Vectors.h"

class Quaternion
{
public:
    Quaternion();
    Quaternion(float _w, float _x, float _y, float _z);
    ~Quaternion();

    Quaternion operator*(Quaternion const& q1);
    Vec3 operator*(Vec3 const& v1);
    Quaternion operator*(float f);
    Quaternion operator+(Quaternion const& q1);
    Quaternion& operator*=(Quaternion const& q1);
    float dot(Quaternion const& q);
    void set(float _w, float _x, float _y, float _z);
    void setFromAxis(float angle, float _x, float _y, float _z);
    Quaternion conjugate();
    Quaternion slerp(Quaternion q1, Quaternion q2, float t);
    void normalize();
    void setRotationMatrix(float* mat);

    float w;
    float x;
    float y;
    float z;

//private:

};

#endif // QUATERNION_H
