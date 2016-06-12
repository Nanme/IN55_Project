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
    for(vector<Particle>::iterator it = data.begin(); it != data.end(); ++it)
    {
        it->speed += gravite*frameRate;
        it->updateParticule(frameRate);
        if(floor)
        {

            if(it->getPosition().y < *floor)
            {
                it->speed.y = -it->speed.y * it->getElast() ;
            }
        }
        if(roof)
        {

            if(it->getPosition().y > *roof)
            {
                it->speed.y = -it->speed.y* it->getElast() ;

            }
        }
        if(wallxLeft)
        {

            if(it->getPosition().x < *wallxLeft)
            {
                it->speed.x = -it->speed.x * it->getElast() ;

            }
        }
        if(wallxRight)
        {

            if(it->getPosition().x > *wallxRight)
            {
                it->speed.x = -it->speed.x * it->getElast() ;

            }
        }
        if(wallzNear)
        {

            if(it->getPosition().z > *wallzNear)
            {
                it->speed.z = -it->speed.z * it->getElast() ;

            }
        }
        if(wallzFar)
        {

            if(it->getPosition().z < *wallzFar)
            {
                it->speed.z = -it->speed.z * it->getElast() ;

            }
        }

    }
}
std::list<GLMatrix> *ParticlePool::getModels()
{
    std::sort(data.begin(),data.end());
    std::list<GLMatrix> *l = new list<GLMatrix>;

    for (vector<Particle>::iterator it = data.begin(); it != data.end(); ++it)
    {
        l->push_back( it->getModel());
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

int ParticlePool::getSize()
{
    return data.size();
}

std::vector<Particle> ParticlePool::findDeadParticle()
{

    std::vector<Particle> deadParticle;
    for (std::vector<Particle>::iterator it = data.begin(); it != data.end(); ++it)
    {

        if (it->getLife() >= it->getLife_ini()) {
            deadParticle.push_back(*it);
        }
    }
    return deadParticle;
}
