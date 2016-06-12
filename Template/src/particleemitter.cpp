#include "particleemitter.h"

ParticleEmitter::ParticleEmitter(int _nbParticle)
{
    nbParticle = _nbParticle;
    emitterPosition = Vec3(0.0f, 0.0f, 0.0f);
}

int ParticleEmitter::getNbParticle() const
{
    return nbParticle;
}
