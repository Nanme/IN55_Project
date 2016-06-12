#include "particle.h"
#include <iostream>

//Builder
float Particle::getLife_ini() const
{
    return life_ini;
}

Particle::Particle(Camera *_camera, float _life)
{
    camera = _camera;
    posCamera = _camera->getRefPosition();
    View = _camera->getRefViewMatrix();
    this->life = _life;
    life_ini = _life;
}

Particle::Particle(Vec3 _startPosition, Vec3 _speed, Camera* _camera, float _life)
{
    position = _startPosition;
    speed = _speed;
    position_ini = position;
    speed_ini = speed;

     weight = 1.0f;
     elast = 1.0f;

    life = _life;
    life_ini = _life;

    distance = -1.0f;

    torque = 1.0f;
    currentRotationZ = 0.0f;

    camera = _camera;
    View = _camera->getRefViewMatrix();
    posCamera = _camera->getRefPosition();
}

//Getter - Setter
Vec3& Particle::getPosition()
{
    return position;
}

Vec3 Particle::getSpeed()
{
    return speed;
}

void Particle::setSpeed(const Vec3 &value)
{
    speed = value;
}

//Physical parameter


float Particle::getWeight()
{
    return weight;
}

//Life
float Particle::getLife()
{
    return life;
}

//Camera parameter
float Particle::getDistance() const
{
    return distance;
}

float Particle::getTorque() const
{
    return torque;
}

void Particle::setTorque(float value)
{
    torque = value;
}

float Particle::getCurrentRotationZ() const
{
    return currentRotationZ;
}

void Particle::setCurrentRotationZ(float value)
{
    currentRotationZ = value;
}

//OpenGL parameter
GLMatrix Particle::getModel() const
{
    return model;
}

void Particle::setModel(const GLMatrix &value)
{
    model = value;
}

Camera *Particle::getCamera() const
{
    return camera;
}

void Particle::setCamera(Camera *value)
{
    camera = value;
    View = value->getRefViewMatrix();
    posCamera = value->getRefPosition();
}

//Particle modification
void Particle::updateParticule(float &deltaTime)
{


    //Update lifetime of the particle
    life -= deltaTime;
    if (life >= 0)
    {
        position = position + speed*deltaTime;

        calculateSquareDistanceToCamera();

        model.m[0][0] = (*View).m[0][0];    model.m[0][1] =  (*View).m[1][0];    model.m[0][2] = (*View).m[2][0];    model.m[0][3] = position.x;
        model.m[1][0] = (*View).m[0][1];    model.m[1][1] =  (*View).m[1][1];    model.m[1][2] = (*View).m[2][1];    model.m[1][3] = position.y;
        model.m[2][0] = (*View).m[0][2];    model.m[2][1] =  (*View).m[1][2];    model.m[2][2] = (*View).m[2][2];    model.m[2][3] = position.z;
        model.m[3][0] = 0;               model.m[3][1] =  0;               model.m[3][2] = 0;               model.m[3][3] = 1;

//        float tmpMat[4*4];
//        camera->m_Orientation.setRotationMatrix(tmpMat);
////        std::cout << "( " << tmpMat[0]  << ", " <<  tmpMat[1]  << ", " << tmpMat[2]  << ", " << tmpMat[3]  << ")" << std::endl;
////        std::cout << "( " << tmpMat[4]  << ", " <<  tmpMat[5]  << ", " << tmpMat[6]  << ", " << tmpMat[7]  << ")" << std::endl;
////        std::cout << "( " << tmpMat[8]  << ", " <<  tmpMat[9]  << ", " << tmpMat[10] << ", " << tmpMat[11] << ")" << std::endl;
////        std::cout << "( " << tmpMat[12] << ", " <<  tmpMat[13] << ", " << tmpMat[14] << ", " << tmpMat[15] << ")" << std::endl;

////        GLMatrix View = GLMatrix();
//        (*View).m[0][0] = tmpMat[0];    (*View).m[0][1] = tmpMat[4];    (*View).m[0][2] = tmpMat[8];    (*View).m[0][3] = tmpMat[12];
//        (*View).m[1][0] = tmpMat[1];    (*View).m[1][1] = tmpMat[5];    (*View).m[1][2] = tmpMat[9];    (*View).m[1][3] = tmpMat[13];
//        (*View).m[2][0] = tmpMat[2];    (*View).m[2][1] = tmpMat[6];    (*View).m[2][2] = tmpMat[10];   (*View).m[2][3] = tmpMat[14];
//        (*View).m[3][0] = tmpMat[3];    (*View).m[3][1] = tmpMat[7];    (*View).m[3][2] = tmpMat[11];   (*View).m[3][3] = tmpMat[15];

///*        GLMatrix rotation = GLMatrix();
//        rotation.m[0][0] = cos(currentRotationZ);    rotation.m[0][1] = -sin(currentRotationZ);    rotation.m[0][2] = 0.0f;    rotation.m[0][3] = 0.0f;
//        rotation.m[1][0] = sin(currentRotationZ);    rotation.m[1][1] = cos(currentRotationZ);     rotation.m[1][2] = 0.0f;    rotation.m[1][3] = 0.0f;
//        rotation.m[2][0] = 0.0f;                     rotation.m[2][1] = 0.0f;                      rotation.m[2][2] = 1.0f;    rotation.m[2][3] = 0.0f;
//        rotation.m[3][0] = 0.0f;                     rotation.m[3][1] = 0.0f;                      rotation.m[3][2] = 0.0f;   rotation.m[3][3] = 1.0f;*/

////        std::cout << "-------------------------------------------" << std::endl << "rotation :" << "------------------------" << std::endl;
////        std::cout << "( " << rotation.data[0]  << ", " <<  rotation.data[1]  << ", " << rotation.data[2]  << ", " << rotation.data[3]  << ")" << std::endl;
////        std::cout << "( " << rotation.data[4]  << ", " <<  rotation.data[5]  << ", " << rotation.data[6]  << ", " << rotation.data[7]  << ")" << std::endl;
////        std::cout << "( " << rotation.data[8]  << ", " <<  rotation.data[9]  << ", " << rotation.data[10] << ", " << rotation.data[11] << ")" << std::endl;
////        std::cout << "( " << rotation.data[12] << ", " <<  rotation.data[13] << ", " << rotation.data[14] << ", " << rotation.data[15] << ")" << std::endl;

//        //Define the translation from the origin to the
//        model.m[0][0] = 1.0f;    model.m[0][1] = 0.0f;    model.m[0][2] = 0.0f;    model.m[0][3] = position.x;
//        model.m[1][0] = 0.0f;    model.m[1][1] = 1.0f;    model.m[1][2] = 0.0f;    model.m[1][3] = position.y;
//        model.m[2][0] = 0.0f;    model.m[2][1] = 0.0f;    model.m[2][2] = 1.0f;    model.m[2][3] = position.z;
//        model.m[3][0] = 0.0f;    model.m[3][1] = 0.0f;    model.m[3][2] = 0.0f;    model.m[3][3] = 1.0f;

        //We compute all matrix in model
        //model = model /** View * rotation*/;

        model = model /** (*View)*/;
    }
    else
    {
        initializeParticule();
    }
}

void Particle::initializeParticule(Vec3 _startPosition, Vec3 _speed )
{
    position_ini = _startPosition;
    speed_ini = _speed;

    initializeParticule();

}
void Particle::initializeParticule(){

    position =position_ini;
    speed = speed_ini;
    life = life_ini;
}

void Particle::calculateSquareDistanceToCamera()
{
 distance = position.getSquaredEuclideanDistance(posCamera);
}

bool operator<(const Particle &a, const Particle &b)
{
    return a.getDistance()>b.getDistance();
}

float& Particle::getElast()
{
    return elast;
}

void Particle::setElast(float _elast)
{
    elast = _elast;
}

void Particle::setLife_ini(float _life)
{
    life_ini = _life;
}
