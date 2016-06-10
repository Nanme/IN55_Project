#include "camera.h"

#include <iostream>

Camera::Camera(){
    // Set the orientation by the Identity Quaternion.
    m_Orientation.set(1, 0, 0, 0);
    m_ViewMatrix = GLMatrix();
    m_ProjectionMatrix = GLMatrix();

    // Set the origin vectors
    forward = Vec3(0.0f, 0.0f, 1.0f);
    right = Vec3(1.0f, 0.0f, 0.0f);
    up = Vec3(0.0f, 1.0f, 0.0f);

    //m_Orientation.setFromAxis(0.0f, 0.0f, 0.0f, 1.0f);
    //std::cout << "Quat : " << m_Orientation.w << " " << m_Orientation.x << " " << m_Orientation.y << " " << m_Orientation.z << std::endl;
}

Camera::Camera(float posX, float posY, float posZ):Camera(){
    m_position.x = posX;
    m_position.y = posY;
    m_position.z = posZ;
}

Camera::Camera(float posX, float posY, float posZ, float ar, float np, float fp, float fov):
    Camera(posX, posY, posZ){
    _aspectRatio = ar;
    _nearPlane = np;
    _farPlane = fp;
    _fieldOfView = fov;
}

Camera::~Camera(){

}

void Camera::translate(float x, float y, float z){
    Vec3 tmpVec;
    tmpVec.x = x;
    tmpVec.y = y;
    tmpVec.z = z;
    float shift = tmpVec.length();
    tmpVec.normalize();

    m_position = m_position + ( (m_Orientation * tmpVec) * shift );

}

Vec3
Camera::getPosition(){
    return m_position;
}

void Camera::translateX(float shift){
    m_position = m_position + ( (m_Orientation * Vec3(-1.0f, 0.0f, 0.0f)) * shift);
}

void Camera::translateY(float shift){
    m_position = m_position + ( (m_Orientation * Vec3(0.0f, -1.0f, 0.0f)) * shift);
}

void Camera::translateZ(float shift){
    m_position = m_position + ( (m_Orientation * Vec3(0.0f, 0.0f, -1.0f)) * shift);
}

void Camera::rotate(float angle, float ax, float ay, float az){
    Vec3 tmpVect;
    tmpVect.x = ax;
    tmpVect.y = ay;
    tmpVect.z = az;
    tmpVect.normalize();

    Quaternion tmpQuat = Quaternion();
    tmpQuat.setFromAxis(angle, tmpVect.x, tmpVect.y, tmpVect.z);

    m_Orientation = m_Orientation * tmpQuat;
    updateVectors();
}

void
Camera::updateVectors(){

    forward = m_Orientation * Vec3(0.0f, 0.0f, -1.0f);
    right = m_Orientation * Vec3(-1.0f, 0.0f, 0.0f);
    up = m_Orientation * Vec3(0.0f, -1.0f, 0.0f);

    forward.normalize();
    right.normalize();
    up.normalize();

    /*std::cout << "forward : x: " << forward.x << " y : " << forward.y << " z : " << forward.z << std::endl;
    std::cout << "right : x: " << right.x << " y : " << right.y << " z : " << right.z << std::endl;
    std::cout << "up : x: " << up.x << " y : " << up.y << " z : " << up.z << std::endl;*/

}


void Camera::rotateX(float angle){
    Quaternion tmpQuat = Quaternion();
    tmpQuat.setFromAxis(angle, 1.0f, 0.0f, 0.0f);

    m_Orientation = m_Orientation * tmpQuat;
    updateVectors();
}

void Camera::rotateY(float angle){
    Quaternion tmpQuat = Quaternion();
    Quaternion saveCurrentQuat;
    saveCurrentQuat.set(m_Orientation.w,
                        m_Orientation.x,
                        m_Orientation.y,
                        m_Orientation.z);
    m_Orientation = Quaternion(1, 0, 0, 0);

    tmpQuat.setFromAxis(angle, 0.0f, 1.0f, 0.0f);


    m_Orientation = tmpQuat * saveCurrentQuat;
    updateVectors();
}

void Camera::rotateZ(float angle){
    Quaternion tmpQuat = Quaternion();
    tmpQuat.setFromAxis(angle, 0.0f, 0.0f, 1.0f);

    m_Orientation = m_Orientation * tmpQuat;
    updateVectors();
}

GLMatrix const& Camera::getViewMatrix(){
    buildViewMatrix();
    return m_ViewMatrix;
}

void Camera::setAspectRatio(float ar){
    _aspectRatio = ar;
    buildProjectionMatrix();
}

void Camera::setPlanes(float np, float fp){
    _nearPlane = np;
    _farPlane = fp;
    buildProjectionMatrix();
}

void Camera::setFOV(float angle){
    _fieldOfView = angle;
    buildProjectionMatrix();
}

GLMatrix const& Camera::getProjectionMatrix(){
    buildProjectionMatrix();
    return m_ProjectionMatrix;
}

void Camera::buildProjectionMatrix(){
    float thetaY = 0.5f * (M_PI * _fieldOfView / 180.0f);
    float tanThetaY = tan(thetaY);
    float tanThetaX = tanThetaY * _aspectRatio;
    float halfW = tanThetaX * _nearPlane;
    float halfH = tanThetaY * _nearPlane;
    float left = -halfW;
    float right = halfW;
    float bottom = -halfH;
    float top = halfH;
    float iWidth = 1.0f / (right - left);
    float iHeight = 1.0f / (top - bottom);
    float iDepth = 1.0f / (_nearPlane - _farPlane);

    m_ProjectionMatrix.m[0][0] = 2.0f * _nearPlane * iWidth ;m_ProjectionMatrix.m[0][1] = 0.0f                          ;m_ProjectionMatrix.m[0][2] = (right + left) * iWidth            ;m_ProjectionMatrix.m[0][3] = 0.0f ;
    m_ProjectionMatrix.m[1][0] = 0.0f                       ;m_ProjectionMatrix.m[1][1] = 2.0f * _nearPlane * iHeight   ;m_ProjectionMatrix.m[1][2] = (top + bottom) * iHeight           ;m_ProjectionMatrix.m[1][3] = 0.0f ;
    m_ProjectionMatrix.m[2][0] = 0.0f                       ;m_ProjectionMatrix.m[2][1] = 0.0f                          ;m_ProjectionMatrix.m[2][2] = -(_farPlane + _nearPlane) * iDepth ;m_ProjectionMatrix.m[2][3] = -2.0f * (_farPlane * _nearPlane) * iDepth ;
    m_ProjectionMatrix.m[3][0] = 0.0f                       ;m_ProjectionMatrix.m[3][1] = 0.0f                          ;m_ProjectionMatrix.m[3][2] = -1.0f                              ;m_ProjectionMatrix.m[3][3] = 0.0f ;
}

void Camera::buildViewMatrix(){
    float * tmpMatRot = new float[16];
    // Get the rotation Matrix from the Quaternion.
    m_Orientation.setRotationMatrix(tmpMatRot);

    m_ViewMatrix.m[0][0] = tmpMatRot[0] ; m_ViewMatrix.m[0][1] = tmpMatRot[1] ; m_ViewMatrix.m[0][2] = tmpMatRot[2] ; m_ViewMatrix.m[0][3] = tmpMatRot[3] ;
    m_ViewMatrix.m[1][0] = tmpMatRot[4] ; m_ViewMatrix.m[1][1] = tmpMatRot[5] ; m_ViewMatrix.m[1][2] = tmpMatRot[6] ; m_ViewMatrix.m[1][3] = tmpMatRot[7] ;
    m_ViewMatrix.m[2][0] = tmpMatRot[8] ; m_ViewMatrix.m[2][1] = tmpMatRot[9] ; m_ViewMatrix.m[2][2] = tmpMatRot[10] ; m_ViewMatrix.m[2][3] = tmpMatRot[11] ;
    m_ViewMatrix.m[3][0] = tmpMatRot[12] ; m_ViewMatrix.m[3][1] = tmpMatRot[13] ; m_ViewMatrix.m[3][2] = tmpMatRot[14] ; m_ViewMatrix.m[3][3] = tmpMatRot[15] ;

    /*for(int i = 0 ; i < 4 ; i++){
        for(int j = 0 ; j < 4 ; j++){
            std::cout << m_ViewMatrix.m[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "------------------" << std::endl;*/

    GLMatrix minusPosition;
    minusPosition.m[0][0] = 1.0f ; minusPosition.m[0][1] = 0.0f ; minusPosition.m[0][2] = 0.0f ; minusPosition.m[0][3] = -m_position.x ;
    minusPosition.m[1][0] = 0.0f ; minusPosition.m[1][1] = 1.0f ; minusPosition.m[1][2] = 0.0f ; minusPosition.m[1][3] = -m_position.y ;
    minusPosition.m[2][0] = 0.0f ; minusPosition.m[2][1] = 0.0f ; minusPosition.m[2][2] = 1.0f ; minusPosition.m[2][3] = -m_position.z ;
    minusPosition.m[3][0] = 0.0f ; minusPosition.m[3][1] = 0.0f ; minusPosition.m[3][2] = 0.0f ; minusPosition.m[3][3] = 1.0f ;

    delete tmpMatRot;

    m_ViewMatrix = m_ViewMatrix * minusPosition;
    //m_ViewMatrix = m_ViewMatrix;



}
