#ifndef PARTICLERENDERER_H
#define PARTICLERENDERER_H

#include <string>
#include <vector>

#include "GlFramework.h"
#include "Object3D.h"

#include "texture.h"

//| 0.0 0.0 0.0 | 0.0f 1.0f 0.0f | 0.0f 1.0f 1.0f | 0.0f 0.0f 1.0f |
//|  1   2   3  |  4    5    6   |  7    8    9   |  10   11   12

class ParticleRenderer : public Object3D
{
private:
    GLfloat m_TabRenderVertices[6*3] = {
        //Triangle 1
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,

        //Triangle 2
        -0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f
    };

    GLfloat m_TabColor[6*3] = {
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
    };

    GLfloat m_uvCoor[6*3] = {
        //Triangle 1
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,

        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
    };

    Texture* texture;

    GLint m_shader_ID;

public:
    ParticleRenderer(char* textureFilePath, GLint _shader_ID);
    ~ParticleRenderer();

    GLfloat* tabVertices();
    GLfloat* tabColor();
    GLfloat* uvCoor();

    void drawShape();

    //TODO : uplade/load
    void uploadNewTexture(char* textureFilePath);
    void removeTexture();

    //TODO remove
    void loadTexture();
};

#endif // PARTICLERENDERER_H
