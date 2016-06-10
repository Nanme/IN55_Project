#ifndef PARTICLEPOOL_H
#define PARTICLEPOOL_H

#include <vector>
#include <list>
#include "particle.h"


class ParticlePool
{
    std::vector<Particle> data;
    float frameRate;
    Camera* camera;
    Vec3 gravite;
    float * ydownFloor;

public:
    ParticlePool(float _frameRate, Camera* _camera);
    void push(Vec3 _startPosition, Vec3 _speed);
    void push(Particle);
    void step();
    std::list<GLMatrix>* getModels();
    void setGravite(Vec3);
    void setxdownFloat(float);
};

#endif // PARTICLEPOOL_H
