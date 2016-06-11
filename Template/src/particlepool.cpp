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
        i->speed += gravite*frameRate;
        i->updateParticule(frameRate);
        if(floor)
        {

            if(i->getPosition().y < *floor)
            {
                i->speed.y = -i->speed.y * i->getElast() ;
            }
        }
        if(roof)
        {

            if(i->getPosition().y > *roof)
            {
                i->speed.y = -i->speed.y* i->getElast() ;

            }
        }
        if(wallxLeft)
        {

            if(i->getPosition().x < *wallxLeft)
            {
                i->speed.x = -i->speed.x * i->getElast() ;

            }
        }
        if(wallxRight)
        {

            if(i->getPosition().x > *wallxRight)
            {
                i->speed.x = -i->speed.x * i->getElast() ;

            }
        }
        if(wallzNear)
        {

            if(i->getPosition().z > *wallzNear)
            {
                i->speed.z = -i->speed.z * i->getElast() ;

            }
        }
        if(wallzFar)
        {

            if(i->getPosition().z < *wallzFar)
            {
                i->speed.z = -i->speed.z * i->getElast() ;

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
