#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include "GlFramework.h"

class Texture
{
private:
    char* path;

    GLint shader_ID;

    GLuint texture_ID;

    QImage image;


public:
    //Builder
    Texture(char* _path, GLint _shader_ID);
    ~Texture();

    //Getter - Setter
    char* getPath() const;
    void setPath(char* _path);
    GLuint getTexture_ID() const;
    void setTexture_ID(const GLuint& _value);
    GLint getShaderID() const;
    void setShaderID(GLint _value);
    QImage getImage() const;

    //Utils
    void loadTexture();
    bool loadImage();
    void closeTexture();
    void updateTexture(char* _path);


};

#endif // TEXTURE_H
