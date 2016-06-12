#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "Object3D.h"
#include "particlerenderer.h"
#include "particle.h"
#include "particlepool.h"
#include "particleemitter.h"

class ParticleSystem //: public Object3D
{
private:
    ParticleRenderer* renderer;

    //Particle* part;
    ParticlePool *PP;
    ParticleEmitter* emitter;

    GLuint verticeRenderBuffer_ID;
    GLuint colorBuffer_ID;
    GLuint centerBuffer_ID;

    GLint shader_ID;

    Camera* camera;

public:
    ParticleSystem(GLint _shader_ID, Camera* Camera, ParticleEmitter* _emitter);
    ~ParticleSystem();
//    void drawShape();
    void update(float deltaTime/*, GLMatrix ViewMatrix*/);
    ParticlePool *getPart() const;
    ParticleRenderer *getRenderer() const;
};

#endif // PARTICLESYSTEM_H
