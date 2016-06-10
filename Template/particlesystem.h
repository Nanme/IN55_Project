#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "Object3D.h"
#include "particlerenderer.h"
#include "particle.h"

class ParticleSystem //: public Object3D
{
private:
    ParticleRenderer* renderer;

    Particle* part;

    GLuint verticeRenderBuffer_ID;
    GLuint colorBuffer_ID;
    GLuint centerBuffer_ID;

    GLint shader_ID;

public:
    ParticleSystem(GLint _shader_ID, Camera* Camera);
    ~ParticleSystem();
//    void drawShape();
    void update(float deltaTime/*, GLMatrix ViewMatrix*/);
    Particle *getPart() const;
    ParticleRenderer *getRenderer() const;
};

#endif // PARTICLESYSTEM_H
