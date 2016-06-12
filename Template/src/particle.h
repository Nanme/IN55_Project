#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vectors.h"
#include "GlFramework.h"
#include "camera.h"

class Particle
{
private:
    //Center parameter
    Vec3 position, position_ini;
    Vec3 speed_ini;


    //Physical parameter
    float weight;
    float elast;

    //Life
    float life;
    float life_ini;

    //Camera parameter
    float distance;
    float torque;
    float currentRotationZ;

    //OpenGL parameter
    GLMatrix model;
    Camera* camera;
    GLMatrix *View;
    Vec3* posCamera;

public:

    Vec3 speed;
    Particle(Camera* _camera, float _life = 5);

    //Builder
    Particle(Vec3 _startPosition, Vec3 _speed, Camera* _camera, float _life = 5);

    //Getter - Setter
    //Center parameter
    Vec3& getPosition() ;
    Vec3 getSpeed() ;
    void setSpeed(const Vec3 &value);

    //Physical parameter
    float &getElast() ;
    void setElast(float);
    float getWeight() ;

    //Life
    float getLife() ;
    void setLife_ini(float);

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
    void updateParticule(float& deltaTime);
    void initializeParticule(Vec3 _startPosition, Vec3 _speed);
    void initializeParticule();
    //Utilities
    void calculateSquareDistanceToCamera();
    float getLife_ini() const;
};

bool operator<(const Particle& a, const Particle& b);

#endif // PARTICLE_H
