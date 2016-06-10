#include "texture.h"

#include <iostream>

#include <QGLWidget>

using namespace std;

//Builder
Texture::Texture(char* _path, GLint _shader_ID)
{
    path = _path;
    shader_ID = _shader_ID;
}

Texture::~Texture()
{
}

//Getter - Setter
char* Texture::getPath() const
{
    return path;
}

void Texture::setPath(char* _path)
{
    path = _path;
}

GLuint Texture::getTexture_ID() const
{
    return texture_ID;
}

void Texture::setTexture_ID(const GLuint &value)
{
    texture_ID = value;
}

GLint Texture::getShaderID() const
{
    return shader_ID;
}

void Texture::setShaderID(GLint _value)
{
    shader_ID = _value;
}

QImage Texture::getImage() const
{
    return image;
}

//Utils
void Texture::loadTexture()
{
    if (image.isNull())
        loadImage();

    glGenTextures(1, &texture_ID);
    cout << "Texture ID : " << texture_ID << endl;

    glBindTexture(GL_TEXTURE_2D, texture_ID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(),
                 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    cout << "Texture loaded" << endl;
}

bool Texture::loadImage()
{

    cout << path << endl;
    if (image.load(path))
    {

        cout << "test" << endl;
        image = QGLWidget::convertToGLFormat(image);
        cout << "Image loaded and converted to OpenGL type ";
        cout <<"(" << image.width() << ", " << image.height() << ")" << endl;
        return true;
    }
    return false;
}

void Texture::closeTexture()
{

}

void Texture::updateTexture(char *_path)
{
    this->path = _path;
    if (loadImage())
    {
        loadTexture();
    }
    else
        cout << "Warning : Image unloaded !" << endl;
}

