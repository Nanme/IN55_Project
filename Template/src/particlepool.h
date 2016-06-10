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
    float * floor, *roof, *wallxRight, *wallxLeft, *wallzNear, *wallzFar;

public:
    ParticlePool(float _frameRate, Camera* _camera);
    void push(Vec3 _startPosition, Vec3 _speed, float life = 5, float elast = 1);
    void push(Particle);
    void step();
    std::list<GLMatrix>* getModels();
    void setGravite(Vec3);
    void setFloor(float);
    void setRoof(float);
    void setWallxRight(float);
    void setWallxLeft(float);
    void setWallzNear(float);
    void setWallzFar(float);
};

#endif // PARTICLEPOOL_H
