#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vectors.h"
#include "GlFramework.h"
#include "camera.h"

class Particle
{
private:
    //Center parameter
    Vec3 position;
    Vec3 direction;

    //Physical parameter
    float speed;
    float weight;

    //Life
    float life;

    //Camera parameter
    float distance;
    float torque;
    float currentRotationZ;

    //OpenGL parameter
    GLMatrix model;
    Camera* camera;

public:


    GLMatrix View;
    //Builder
    Particle(Vec3 _startPosition, Vec3 _direction, float _speed, Camera* _camera);

    //Getter - Setter
    //Center parameter
    Vec3 getPosition() const;
    Vec3 getDirection() const;
    void setDirection(const Vec3 &value);

    //Physical parameter
    float getSpeed() const;
    float getWeight() const;

    //Life
    float getLife() const;

    //Camera parameter
    float getDistance() const;
    float getCurrentRotationZ() const;
    void setCurrentRotationZ(float value);
    float getTorque() const;
    void setTorque(float value);

    //OpenGL parameter
    GLMatrix getModel() const;
    void setModel(const GLMatrix &value);
    Camera *getCamera() const;
    void setCamera(Camera *value);

    //Particle modification
    void updateParticule(float deltaTime);
    void initializeParticule(Vec3 _startPosition, Vec3 _direction, float _speed);

    //Utilities
    void calculateDistanceToCamera();
};

bool operator<(const Particle& a, const Particle& b);

#endif // PARTICLE_H
