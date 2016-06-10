#include "particlesystem.h"
#include "particlepool.h"


GLfloat g_Vertices[6*3];

ParticlePool *ParticleSystem::getPart() const
{
    return PP;
}

ParticleRenderer *ParticleSystem::getRenderer() const
{
    return renderer;
}

ParticleSystem::ParticleSystem(GLint _shader_ID, Camera* camera)
{
    renderer = new ParticleRenderer("tex2d_pikachu.png", _shader_ID);
    PP = new ParticlePool(1.0f/30.f,camera);

    PP->setGravite(Vec3(10.0f,10.0f,5.0f));
    PP->setFloor(-2.5f);
    //PP->setWallxRight(2.5f);
    PP->setWallzNear(20.f);
    PP->setRoof(8.f);
    PP->setWallxLeft(-2.5f);
   // PP->setWallzFar(-2.5f);

    const float ELAST = 1.0f, LIFE = 10.0f;

    PP->push(Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 5.0f, 0.0f),LIFE,ELAST);
    PP->push(Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f),LIFE,ELAST);
    PP->push(Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 0.0f, 1.0f),LIFE,ELAST);
    PP->push(Vec3(0.0f, 1.0f, 4.0f), Vec3(0.20f, 5.0f, 0.0f),LIFE,ELAST);
    PP->push(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.30f, 1.8f, 0.0f),LIFE,ELAST);
    PP->push(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 1.0f),LIFE,ELAST);
    PP->push(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f,- 1.0f, 5.0f),LIFE,ELAST);
    PP->push(Vec3(0.0f, 0.0f, 0.0f), Vec3(4.0f, 1.5f, 0.0f),LIFE,ELAST);
    PP->push(Vec3(0.0f, 0.0f, 0.0f), Vec3(2.0f, -1.5f, 0.0f),LIFE,ELAST);
    PP->push(Vec3(0.0f, 0.0f, 0.0f), Vec3(3.0f, 1.0f, 0.0f),LIFE,ELAST);
    PP->push(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, -1.8f, 4.f),LIFE,ELAST);
    PP->push(Vec3(0.0f, 0.0f, 0.0f), Vec3(3.0f, -1.0f, 4.0f),LIFE,ELAST);

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
//    part->updateParticule(deltaTime);
//    GLfloat sizez = part->getSize();
//    Vec3 center = part->getPosition();

//    Vec3 cameraRight(ViewMatrix.m[0][0], ViewMatrix.m[1][0], ViewMatrix.m[2][0]);
//    Vec3 cameraUp(ViewMatrix.m[0][1], ViewMatrix.m[1][1], ViewMatrix.m[2][1]);

//    Vec3 tmp[6];

//    GLfloat result[6*3];

//    for (int i = 0; i<6*3; i+=3)
//    {
//        tmp[i%3] = Vec3(renderer->tabVertices()[i], renderer->tabVertices()[i+1], renderer->tabVertices()[3]);
//    }/*

//    for(int i = 0; i<6; ++i)
//    {
//        tmp[i] = center + cameraRight*sizez*tmp[i].x + cameraUp*tmp[i].y*sizez;
//    }*/

//    for (int i = 0; i<6*3; i++){
//        switch(i%3)
//        {
//        case 0:
//            result[i] = tmp[i%6].x;
//            break;
//        case 1:
//            result[i] = tmp[i%6].y;
//            break;
//        case 2:
//            result[i] = tmp[i%6].z;
//            break;
//        }
//    }
    PP->step();

//    glBufferSubData(GL_ARRAY_BUFFER, 0, 4*sizeof(GLfloat), center);
}
