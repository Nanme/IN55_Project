#include "quaternion.h"

Quaternion::Quaternion()
{
    w = 0;
    x = 0;
    y = 0;
    z = 0;
}

Quaternion::Quaternion(float _w, float _x, float _y, float _z){
    w = _w;
    x = _x;
    y = _y;
    z = _z;
}

Quaternion::~Quaternion(){

}

Quaternion Quaternion::operator*(Quaternion const& q1){
    Quaternion tmpQuat;
    float newS;
    Vec3 v1 ;
    Vec3 v2 ;
    Vec3 v3 ;

    v1.x = x;
    v1.y = y;
    v1.z = z;

    v2.x = q1.x ;
    v2.y = q1.y ;
    v2.z = q1.z ;

    newS = w*q1.w - v1.dotProduct(v2);

    v3 = v1.crossProduct(v2);

    v1 = v1 * q1.w;
    v2 = v2 * w;

    v3 = v1 + v2 + v3;

    tmpQuat.set(newS, v3.x, v3.y, v3.z);
    tmpQuat.normalize();

    return tmpQuat;

}



Vec3 Quaternion::operator*(Vec3 const& v1){
    Quaternion point = Quaternion(0, v1.x, v1.y, v1.z);

    Quaternion res = *this * point * conjugate();

    Vec3 vRes;
    vRes.x = res.x;
    vRes.y = res.y;
    vRes.z = res.z;

    return vRes;
}



Quaternion Quaternion::operator*(float f){
    Quaternion tmpQuat = Quaternion();

    tmpQuat.w = w * f;
    tmpQuat.x = x * f;
    tmpQuat.y = y * f;
    tmpQuat.z = z * f;

    return tmpQuat;
}

Quaternion Quaternion::operator+(Quaternion const& q1){
    return Quaternion(w + q1.w, x + q1.x, y + q1.y, z + q1.z);
}

Quaternion& Quaternion::operator*=(Quaternion const& q1){
    Quaternion tmpQuat = *this;
    float newS;
    Vec3 v1 ;
    Vec3 v2 ;
    Vec3 v3 ;

    v1.x = x;
    v1.y = y;
    v1.z = z;

    v2.x = q1.x ;
    v2.y = q1.y ;
    v2.z = q1.z ;

    newS = w*q1.w - v1.dotProduct(v2);

    v3 = v1.crossProduct(v2);

    v1 = v1 * q1.w;
    v2 = v2 * w;

    v3 = v1 + v2 + v3;

    this->set(newS, v3.x, v3.y, v3.z);
    this->normalize();

    return *this;
}

float Quaternion::dot(Quaternion const& q){
    return w*q.w + x*q.x + y*q.y + z*q.z;
}

void Quaternion::set(float _w, float _x, float _y, float _z){
    w = _w;
    x = _x;
    y = _y;
    z = _z;
}

void Quaternion::setFromAxis(float angle, float _x, float _y, float _z){
    Vec3 v = Vec3(_x, _y, _z);
    v.normalize();

    w = cos( angle / 2.0d ) ;
    x = v.x*sin( angle / 2.0d ) ;
    y = v.y*sin( angle / 2.0d ) ;
    z = v.z*sin( angle / 2.0d ) ;
    normalize();
}

Quaternion Quaternion::conjugate(){
    return Quaternion(w, -x, -y, -z);
}

Quaternion Quaternion::slerp(Quaternion q1, Quaternion q2, float t){
    Quaternion currentQuaternion = Quaternion();

    // (q2*q1)^t q1

    float sinTheta = sqrt(1.0f - pow(q1.dot(q2), 2.0d));

    currentQuaternion = (q1*((sinTheta*(1-t))/sinTheta)) + q2*((sinTheta*t)/sinTheta);

    return currentQuaternion;
}

void Quaternion::normalize(){
    float magnitude = sqrt(w*w + x*x +y*y + z*z);
    w /= magnitude;
    x /= magnitude;
    y /= magnitude;
    z /= magnitude;
}

void Quaternion::setRotationMatrix(float* mat){
    // We verify if the matrix is null if it's the case we delete it.

    mat[0] = 1.0f - (2.0f*y*y) - (2.0f*z*z)  ; mat[4] = (2.0f*x*y) - (2.0f*w*z)        ; mat[8] = (2.0f*x*z) + (2.0f*w*y)         ; mat[12] = 0.0f ;
    mat[1] = (2.0f*x*y) + (2.0f*w*z)         ; mat[5] = 1.0f - (2.0f*x*x) - (2.0f*z*z) ; mat[9] = (2.0f*y*z) - (2.0f*w*x)         ; mat[13] = 0.0f ;
    mat[2] = (2.0f*x*z) - (2.0f*w*y)         ; mat[6] = (2.0f*y*z) + (2.0f*w*x)        ; mat[10] = 1.0f - (2.0f*x*x) - (2.0f*y*y) ; mat[14] = 0.0f ;
    mat[3] = 0.0f                            ; mat[7] = 0.0f                           ; mat[11] = 0.0f                           ; mat[15] = 1.0f ;
}


