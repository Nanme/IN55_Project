#include "particlepool.h"
#include <algorithm>


using namespace std;

ParticlePool::ParticlePool(float _frameRate, Camera* _camera)
{
    frameRate = _frameRate;
    camera = _camera;
    gravite = Vec3(0,0,0);
}

void ParticlePool::push(Vec3 _startPosition, Vec3 _speed)
{
    Particle p(_startPosition, _speed, camera);
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
        i->setDirection(i->getDirection() + gravite*frameRate);
        i->updateParticule(frameRate);
        if(ydownFloor)
        {
            Vec3 tmp = i->getDirection();
            if(tmp.y < *ydownFloor)
            {
                tmp.y = -tmp.y  ;
                i->setDirection(tmp);

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

void ParticlePool::setxdownFloat(float distance)
{
    if(ydownFloor)
        delete ydownFloor;
    ydownFloor = new float(distance);
}
