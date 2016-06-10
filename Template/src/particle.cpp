#include "particle.h"
#include <iostream>

//Builder
Particle::Particle(Vec3 _startPosition, Vec3 _direction, float _speed, Camera* _camera)
{
    position = _startPosition;
    direction = _direction;

    speed = _speed;
    weight = 1.0f;

    life = 5.0f;

    distance = -1.0f;
    // ?????
    torque = M_PI/4;
    currentRotationZ = 0.0f;

    camera = _camera;
}

//Getter - Setter
Vec3 Particle::getPosition() const
{
    return position;
}

Vec3 Particle::getDirection() const
{
    return direction;
}

void Particle::setDirection(const Vec3 &value)
{
    direction = value;
}

//Physical parameter
float Particle::getSpeed() const
{
    return speed;
}

float Particle::getWeight() const
{
    return weight;
}

//Life
float Particle::getLife() const
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
}

//Particle modification
void Particle::updateParticule(float deltaTime)
{
    //Update lifetime of the particle
    life -= deltaTime;

    //Check if the particle is always alive
    if (life > 0.0f)
    {
        std::cout << "life : " << life << " | deltaTime : " << deltaTime << std::endl;
        //Then we update the parameter of the center of the particle
        direction = direction * speed * deltaTime;
        position = position + direction;
        direction.normalize();

        std::cout << "position (" << position.x << ", " << position.y << ", " << position.z << ")" << std::endl;
        std::cout << "speed : " << speed << std::endl;

        //?????????????
        currentRotationZ = torque * deltaTime;

        calculateDistanceToCamera();

        //Get the rotation of the camera
        float tmpMat[4*4];
        camera->m_Orientation.setRotationMatrix(tmpMat);
        std::cout << "( " << tmpMat[0]  << ", " <<  tmpMat[1]  << ", " << tmpMat[2]  << ", " << tmpMat[3]  << ")" << std::endl;
        std::cout << "( " << tmpMat[4]  << ", " <<  tmpMat[5]  << ", " << tmpMat[6]  << ", " << tmpMat[7]  << ")" << std::endl;
        std::cout << "( " << tmpMat[8]  << ", " <<  tmpMat[9]  << ", " << tmpMat[10] << ", " << tmpMat[11] << ")" << std::endl;
        std::cout << "( " << tmpMat[12] << ", " <<  tmpMat[13] << ", " << tmpMat[14] << ", " << tmpMat[15] << ")" << std::endl;

//        GLMatrix View = GLMatrix();
        View.m[0][0] = tmpMat[0];    View.m[0][1] = tmpMat[1];    View.m[0][2] = tmpMat[2];    View.m[0][3] = tmpMat[3];
        View.m[1][0] = tmpMat[4];    View.m[1][1] = tmpMat[5];    View.m[1][2] = tmpMat[6];    View.m[1][3] = tmpMat[7];
        View.m[2][0] = tmpMat[8];    View.m[2][1] = tmpMat[9];    View.m[2][2] = tmpMat[10];   View.m[2][3] = tmpMat[11];
        View.m[3][0] = tmpMat[12];   View.m[3][1] = tmpMat[13];   View.m[3][2] = tmpMat[14];   View.m[3][3] = tmpMat[15];

        GLMatrix rotation = GLMatrix();
        rotation.m[0][0] = cos(M_PI/4);    rotation.m[0][1] = -sin(M_PI/4);    rotation.m[0][2] = 0.0f;    rotation.m[0][3] = 0.0f;
        rotation.m[1][0] = sin(M_PI/4);    rotation.m[1][1] = cos(M_PI/4);     rotation.m[1][2] = 0.0f;    rotation.m[1][3] = 0.0f;
        rotation.m[2][0] = 0.0f;                     rotation.m[2][1] = 0.0f;                      rotation.m[2][2] = 1.0f;    rotation.m[2][3] = 0.0f;
        rotation.m[3][0] = 0.0f;                     rotation.m[3][1] = 0.0f;                      rotation.m[3][2] = 0.0f;    rotation.m[3][3] = 1.0f;

//        std::cout << "-------------------------------------------" << std::endl << "rotation :" << "------------------------" << std::endl;
//        std::cout << "( " << rotation.data[0]  << ", " <<  rotation.data[1]  << ", " << rotation.data[2]  << ", " << rotation.data[3]  << ")" << std::endl;
//        std::cout << "( " << rotation.data[4]  << ", " <<  rotation.data[5]  << ", " << rotation.data[6]  << ", " << rotation.data[7]  << ")" << std::endl;
//        std::cout << "( " << rotation.data[8]  << ", " <<  rotation.data[9]  << ", " << rotation.data[10] << ", " << rotation.data[11] << ")" << std::endl;
//        std::cout << "( " << rotation.data[12] << ", " <<  rotation.data[13] << ", " << rotation.data[14] << ", " << rotation.data[15] << ")" << std::endl;

        //Define the translation from the origin to the
        model.m[0][0] = 1.0f;    model.m[0][1] = 0.0f;    model.m[0][2] = 0.0f;    model.m[0][3] = position.x;
        model.m[1][0] = 0.0f;    model.m[1][1] = 1.0f;    model.m[1][2] = 0.0f;    model.m[1][3] = position.y;
        model.m[2][0] = 0.0f;    model.m[2][1] = 0.0f;    model.m[2][2] = 1.0f;    model.m[2][3] = position.z;
        model.m[3][0] = 0.0f;    model.m[3][1] = 0.0f;    model.m[3][2] = 0.0f;    model.m[3][3] = 1.0f;

        //We compute all matrix in model
        model = model /** View * rotation*/;

        std::cout << "-------------------------------------------" << std::endl << "rotation :" << "------------------------" << std::endl;
        std::cout << "( " << model.data[0]  << ", " <<  model.data[1]  << ", " << model.data[2]  << ", " << model.data[3]  << ")" << std::endl;
        std::cout << "( " << model.data[4]  << ", " <<  model.data[5]  << ", " << model.data[6]  << ", " << model.data[7]  << ")" << std::endl;
        std::cout << "( " << model.data[8]  << ", " <<  model.data[9]  << ", " << model.data[10] << ", " << model.data[11] << ")" << std::endl;
        std::cout << "( " << model.data[12] << ", " <<  model.data[13] << ", " << model.data[14] << ", " << model.data[15] << ")" << std::endl;
    }
    else
    {
        position = Vec3(0.0f, 0.0f, 0.0f);
        direction = Vec3(1.0f, 1.0f, 0.0f);

        life = 5.0f;
    }
}

void Particle::initializeParticule(Vec3 _startPosition, Vec3 _direction, float _speed)
{
    position = _startPosition;
    direction = _direction;
    speed = _speed;
    life = 5.0f;

    calculateDistanceToCamera();
}

void Particle::calculateDistanceToCamera()
{

}

bool operator<(const Particle &a, const Particle &b)
{
    return a.getDistance()<b.getDistance();
}
