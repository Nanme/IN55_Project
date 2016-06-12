#ifndef CONEEMITTER_H
#define CONEEMITTER_H

#include "particleemitter.h"

#include <ctime>


class ConeEmitter : public ParticleEmitter
{
    float downRadius;
    float upRadius;
    float height;

    float speed;

public:
    ConeEmitter(float _downRadius, float _upRadius, float _height, float _speed, int _nbParticle);
    void createParticle(Particle *);
};

#endif // CONEEMITTER_H
