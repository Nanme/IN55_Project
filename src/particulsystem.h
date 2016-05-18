#ifndef PARTICULSYSTEM_H
#define PARTICULSYSTEM_H

#include "particulemitter.h"
#include "renderer.h"
#include "objectpool.h"
#include "framework/GlFramework.h"


class ParticulSystem
{
private:
    //Particul system
    ParticulEmitter* emitter;
    Renderer* render;
    ObjectPool* pool;

    //FrameWork
    GlFramework* framework;
public:
    ParticulSystem();
    ~ParticulSystem();
};

#endif // PARTICULSYSTEM_H
