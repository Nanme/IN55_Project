#ifndef RENDERER_H
#define RENDERER_H

#include "framework/Object3D.h"

class Renderer : public Object3D
{
private:
    const GLfloat tabVertice[12] = {
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f
    };

    const GLuint tabIndice[4] = {0, 1, 2, 3};
public:
    Renderer();
    void drawShape();
};

#endif // RENDERER_H
