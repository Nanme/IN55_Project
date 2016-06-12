#ifndef PARTICLEEMITER_H
#define PARTICLEEMITER_H

#include "particle.h"


class ParticleEmitter
{
private:
    Vec3 emitterPosition;
    int nbParticle;

public:
    ParticleEmitter(int _nbParticle);

    virtual void createParticle(Particle *) = 0;
    int getNbParticle() const;
};

#endif // PARTICLEEMITER_H
