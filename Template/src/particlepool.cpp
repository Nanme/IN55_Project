#include "particlepool.h"
#include <algorithm>


using namespace std;

ParticlePool::ParticlePool(float _frameRate, Camera* _camera)
{
    frameRate = _frameRate;
    camera = _camera;
    gravite = Vec3(0,0,0);
    floor = NULL;
    roof = NULL;
    wallxLeft= NULL;
    wallxRight = NULL;
    wallzFar = NULL;
    wallzNear = NULL;
}

void ParticlePool::push(Vec3 _startPosition, Vec3 _speed, float life, float elast )
{
    Particle p(_startPosition, _speed, camera, life);
    p.setElast(elast);
    data.push_back(p);
}

void ParticlePool::push(Particle p)
{
    data.push_back(p);
}

void ParticlePool::step()
{
    for(vector<Particle>::iterator i = data.begin(); i != data.end(); ++i)
    {
        i->setSpeed(i->getSpeed() + gravite*frameRate);
        i->updateParticule(frameRate);
        if(floor)
        {
            Vec3 tmp = i->getSpeed();
            if(i->getPosition().y < *floor)
            {
                tmp.y = -tmp.y * i->getElast() ;
                i->setSpeed(tmp);

            }
        }
        if(roof)
        {
            Vec3 tmp = i->getSpeed();
            if(i->getPosition().y > *roof)
            {
                tmp.y = -tmp.y* i->getElast() ;
                i->setSpeed(tmp);

            }
        }
        if(wallxLeft)
        {
            Vec3 tmp = i->getSpeed();
            if(i->getPosition().x < *wallxLeft)
            {
                tmp.x = -tmp.x * i->getElast() ;
                i->setSpeed(tmp);

            }
        }
        if(wallxRight)
        {
            Vec3 tmp = i->getSpeed();
            if(i->getPosition().x > *wallxRight)
            {
                tmp.x = -tmp.x * i->getElast() ;
                i->setSpeed(tmp);

            }
        }
        if(wallzNear)
        {
            Vec3 tmp = i->getSpeed();
            if(i->getPosition().z > *wallzNear)
            {
                tmp.z = -tmp.z * i->getElast() ;
                i->setSpeed(tmp);

            }
        }
        if(wallzFar)
        {
            Vec3 tmp = i->getSpeed();
            if(i->getPosition().z < *wallzFar)
            {
                tmp.z = -tmp.z * i->getElast() ;
                i->setSpeed(tmp);

            }
        }

    }
}
std::list<GLMatrix> *ParticlePool::getModels()
{
    std::sort(data.begin(),data.end());
    std::list<GLMatrix> *l = new list<GLMatrix>;
    for (vector<Particle>::iterator i = data.begin(); i != data.end(); ++i)
    {
       l->push_back( i->getModel());
    }
    return l;
}

void ParticlePool::setGravite(Vec3 _gravite)
{
    gravite  = _gravite;
}

void ParticlePool::setFloor(float distance)
{
    if(floor)
        delete floor;
    floor = new float(distance);
}


void ParticlePool::setRoof(float f)
{

    if(roof)
        delete roof;
    roof = new float(f);
}

void ParticlePool::setWallxRight(float f)
{

    if(wallxRight)
        delete wallxRight;
    wallxRight = new float(f);
}

void ParticlePool::setWallxLeft(float f)
{

    if(wallxLeft)
        delete wallxLeft;
    wallxLeft= new float(f);
}

void ParticlePool::setWallzNear(float f)
{

    if(wallzNear)
        delete wallzNear;
    wallzNear= new float(f);
}

void ParticlePool::setWallzFar(float f)
{

    if(wallzFar)
        delete wallzFar;
    wallzFar = new float(f);
}
