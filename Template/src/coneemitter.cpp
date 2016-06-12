#include "coneemitter.h"

ConeEmitter::ConeEmitter(float _downRadius, float _upRadius, float _height, float _speed,  int _nbParticle) : ParticleEmitter(_nbParticle)
{
    downRadius = _downRadius;
    upRadius = _upRadius;
    height = _height;
    speed = _speed;
    srand(time(NULL));
}

void ConeEmitter::createParticle(Particle* p)
{
    GLfloat theta = (rand()%360)*2*M_PI/360;
    GLfloat x = cos(theta);
    GLfloat z = sin(theta);

    Vec3 position(x*downRadius, 0.0f, z*downRadius);
    Vec3 direction = Vec3(x*upRadius, height, z*upRadius) - position;
    direction.normalize();

    p->initializeParticule(position, direction*speed);

}
