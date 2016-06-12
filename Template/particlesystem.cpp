#include "particlesystem.h"
#include "particlepool.h"

ParticleSystem::ParticleSystem(GLint _shader_ID, Camera* _camera, ParticleEmitter* _emitter)
{
    renderer = new ParticleRenderer("FireParticleSingleTexture.png", _shader_ID);
    PP = new ParticlePool(1.0f/60.f,camera);
    emitter = _emitter;
    camera = _camera;

    PP->setGravite(Vec3(0.0f,-1.0f,0.0f));

//    PP->setFloor(-2.5f);
//    PP->setWallxRight(1.0f);
//    PP->setWallzNear(20.f);
//   PP->setRoof(3.f);
//    PP->setWallxLeft(-2.5f);
//    PP->setWallzFar(-2.5f);

//    const float ELAST = 1.0f, LIFE = 5.0f;

//    PP->push(Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 5.0f, 0.0f),LIFE,ELAST);
//    PP->push(Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f),LIFE,ELAST);
//    PP->push(Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 0.0f, 1.0f),LIFE,ELAST);
//    PP->push(Vec3(0.0f, 1.0f, 4.0f), Vec3(0.20f, 5.0f, 0.0f),LIFE,ELAST);
//    PP->push(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.30f, 1.8f, 0.0f),LIFE,ELAST);
//    PP->push(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 1.0f),LIFE,ELAST);
//    PP->push(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f,- 1.0f, 5.0f),LIFE,ELAST);
//    PP->push(Vec3(0.0f, 0.0f, 0.0f), Vec3(4.0f, 1.5f, 0.0f),LIFE,ELAST);
//    PP->push(Vec3(0.0f, 0.0f, 0.0f), Vec3(2.0f, -1.5f, 0.0f),LIFE,ELAST);
//    PP->push(Vec3(0.0f, 0.0f, 0.0f), Vec3(3.0f, 1.0f, 0.0f),LIFE,ELAST);
//    PP->push(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, -1.8f, 4.f),LIFE,ELAST);
//    PP->push(Vec3(0.0f, 0.0f, 0.0f), Vec3(3.0f, -1.0f, 4.0f),LIFE,ELAST);



    // part = new Particle(Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 1.0f, 0.0f), 5.0f, camera);
    this->shader_ID = _shader_ID;

//   //Create vertices buffer
//   glGenBuffers(1, &verticeRenderBuffer_ID);
//   glBindBuffer(GL_ARRAY_BUFFER, verticeRenderBuffer_ID);
//   glBufferData(GL_ARRAY_BUFFER, sizeof(renderer->tabVertices()), renderer->tabVertices(), GL_STATIC_DRAW);

//   //Create color buffer
//   glGenBuffers(1, &colorBuffer_ID);
//   glBindBuffer(GL_ARRAY_BUFFER, colorBuffer_ID);
//   glBufferData(GL_ARRAY_BUFFER, sizeof(renderer->tabColor()), renderer->tabColor(), GL_STREAM_DRAW);

//   //Create center buffer
//   glGenBuffers(1, &centerBuffer_ID);
//   glBindBuffer(GL_ARRAY_BUFFER, centerBuffer_ID);
//   glBufferData(GL_ARRAY_BUFFER, 4*sizeof(GLfloat), NULL, GL_STREAM_DRAW);
}


ParticlePool *ParticleSystem::getPart() const
{
    return PP;
}

ParticleRenderer *ParticleSystem::getRenderer() const
{
    return renderer;
}

ParticleSystem::~ParticleSystem()
{
    //delete part;
    delete renderer,PP;
}

/*void ParticleSystem::drawShape()
{
//    //Vertices
//    glEnableVertexAttribArray(0);
//    glBindBuffer(GL_ARRAY_BUFFER, verticeRenderBuffer_ID);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

//    //color
//    glEnableVertexAttribArray(1);
//    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer_ID);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

//    //position
//    glEnableVertexAttribArray(2);
//    glBindBuffer(GL_ARRAY_BUFFER, centerBuffer_ID);
//    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

//    //Define the number of uses of each buffer
//    glVertexAttribDivisorARB(0,0);
//    glVertexAttribDivisorARB(1,1);
//    glVertexAttribDivisorARB(2,1);

//    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 1);

    GLfloat centers[6*4];
    for (int i = 0; i<6; ++i)
    {
        switch (i%4)
        {
        case 0:
            centers[i] = part->getPosition().x;
            break;
        case 1:
            centers[i] = part->getPosition().y;
            break;
        case 2:
            centers[i] = part->getPosition().z;
            break;
        case 3:
            centers[i] = part->getSize();
            break;
        default:
            break;
        }
    }

    GLint renderVertices_ID = glGetAttribLocation(shader_ID, "renderVertice");
    glEnableVertexAttribArray(renderVertices_ID);
    glVertexAttribPointer(renderVertices_ID, 3, GL_FLOAT, GL_FALSE, 0, renderer->tabVertices());

    GLint color_ID = glGetAttribLocation(shader_ID, "renderVertice");
    glEnableVertexAttribArray(color_ID);
    glVertexAttribPointer(color_ID, 3, GL_FLOAT, GL_FALSE, 0, renderer->tabColor());

    GLint centers_ID = glGetAttribLocation(shader_ID, "renderVertice");
    glEnableVertexAttribArray(centers_ID);
    glVertexAttribPointer(centers_ID, 2, GL_FLOAT, GL_FALSE, 0, renderer->uvCoor());

    glDrawArrays(GL_TRIANGLES, 0, 6*3);


    glDisableVertexAttribArray( renderVertices_ID );
    glDisableVertexAttribArray( color_ID );
//    glDisableVertexAttribArray( centers_ID );
}*/

void ParticleSystem::update(float deltaTime/*, GLMatrix ViewMatrix*/)
{

    int nbParticle = emitter->getNbParticle();
    Particle* p;
    if (PP->getSize() < nbParticle)
    {
        //We calculate the number of particle to generate in this frame.
        int nbNewParticle = deltaTime * nbParticle;
        //We check if the new number of particle will be greater than the max number of particle.
        if(PP->getSize() + nbNewParticle > nbParticle)
            nbNewParticle = nbParticle - PP->getSize() + nbNewParticle;
        for (int i = 0; i<=nbNewParticle; ++i)
        {
            p = new Particle(camera);
            emitter->createParticle(p);
            PP->push(*p);
        }

    }
    else
    {
        std::vector<Particle> deadParticle = PP->findDeadParticle();

        for (std::vector<Particle>::iterator it = deadParticle.begin(); it != deadParticle.end(); ++it)
        {

            emitter->createParticle(&(*it));
        }
    }
    PP->step();
}
