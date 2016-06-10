#include "particlerenderer.h"

#include <iostream>
#include <vector>

#include <QImage>
#include <QGLWidget>

//#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>


#include "SOIL\SOIL.h"
#include "lodepng\lodepng.h"

using namespace std;

ParticleRenderer::ParticleRenderer(char* textureFilePath, GLint _shader_ID)
{
    m_shader_ID = _shader_ID;
    texture = new Texture(textureFilePath, _shader_ID);
    texture->loadTexture();

//    //Create vertices buffer
//    glGenBuffers(1, verticeRenderBuffer_ID);
//    glBindBuffer(GL_ARRAY_BUFFER, verticeRenderBuffer_ID);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(m_TabVertices), GL_STATIC_DRAW);

//    //Create color buffer
//    glGenBuffers(1, colorBuffer_ID);
//    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer_ID);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(m_TabColor), m_TabColor, GL_STREAM_DRAW);


}

ParticleRenderer::~ParticleRenderer()
{
    delete texture;
}

GLfloat* ParticleRenderer::tabVertices()
{
    return m_TabRenderVertices;
}

GLfloat* ParticleRenderer::tabColor()
{
    return m_TabColor;
}

GLfloat *ParticleRenderer::uvCoor()
{
    return m_uvCoor;
}

void ParticleRenderer::drawShape()
{

    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);

    //Indices version
    /*-------------------------------------------------------------------------------------
    //Attribute m_TabVertices to position var in shader.
    GLint position_ID = glGetAttribLocation( m_Framework->getCurrentShaderId(), "position" );
    glEnableVertexAttribArray( position_ID );
    glVertexAttribPointer( position_ID, 3, GL_FLOAT, GL_FALSE, 0, m_TabVertices );

    //Attribute m_TabColor to position in shader
    GLint color_ID = glGetAttribLocation( m_Framework->getCurrentShaderId(), "color" );
    glEnableVertexAttribArray( color_ID );
    glVertexAttribPointer( color_ID, 3, GL_FLOAT, GL_FALSE, 0, m_TabColor );

    //Attribute uv coordonate
    GLint uv_ID = glGetAttribLocation( m_Framework->getCurrentShaderId(), "uv");
    glEnableVertexAttribArray(uv_ID);
    glVertexAttribPointer(uv_ID, 2, GL_FLOAT, GL_FALSE, 0, m_uvCoor);

    //Draw elements
    glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, m_TabIndices);
    --------------------------------------------------------------------------------------*/

    //Arrays version
    //Vertices
    GLint renderVertices_ID = glGetAttribLocation( m_shader_ID, "renderVertice" );
    glEnableVertexAttribArray(renderVertices_ID);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, m_TabRenderVertices);

    //Color
    GLint color_ID = glGetAttribLocation( m_shader_ID, "color" );
    glEnableVertexAttribArray(color_ID);
    glVertexAttribPointer(color_ID, 3, GL_FLOAT, GL_FALSE, 0, m_TabColor);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //UV
    GLint uv_ID = glGetAttribLocation( m_shader_ID, "uv" );
    glEnableVertexAttribArray(uv_ID);
    glVertexAttribPointer(uv_ID, 2, GL_FLOAT, GL_FALSE, 0, m_uvCoor);

    glDrawArrays(GL_TRIANGLES, 0, 6*3);

    //Remove shader var
    glDisableVertexAttribArray( renderVertices_ID );
    glDisableVertexAttribArray( color_ID );
    glDisableVertexAttribArray( uv_ID );
}

void ParticleRenderer::uploadNewTexture(char* textureFilePath)
{
    texture->updateTexture(textureFilePath);
}

void ParticleRenderer::removeTexture()
{
    texture->closeTexture();
}

//TODO : to remove
void ParticleRenderer::loadTexture()
{
    cout << "Start loadTexture()" << endl;
    cout << "Start load png" << endl;

    //QImage version
    GLuint tex_id;
    QImage image;

    if(image.load("m_texture_path"))
    {
        cout << "test" << endl;
//        int shader_id = m_Framework->getCurrentShaderId();
//        cout << "sid" << shader_id;
//        GLuint TextureID  = glGetUniformLocation(m_Framework->getCurrentShaderId(), "mytexture");
        cout << "test";

        image = QGLWidget::convertToGLFormat(image);

        glGenTextures(1, &tex_id);

        cout << "Texture " << tex_id << " loaded : " << "width : " << image.width() << "height : " << image.height() << endl;


//        glActiveTexture(GL_TEXTURE0);
        glBindTexture( GL_TEXTURE_2D, tex_id );
//        glUniform1i(TextureID, 0);
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits() );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    //SDL version
    /*-----------------------------------------------------------------------------------
    SDL_Surface *imageSDL = IMG_Load(m_texture_path);
    GLenum encodageInterne, encodage;

    if (imageSDL == 0){
        std::cout << "Erreur : " << SDL_GetError() << std::endl;
        return;
    }

    SDL_FreeSurface(imageSDL);

    glGenTextures(1, &m_texture_ID);

    glBindTexture(GL_TEXTURE_2D, m_texture_ID);

    if (imageSDL->format->BytesPerPixel == 3){
        encodageInterne = GL_RGB;
        if (imageSDL->format->Rmask == 0xff)
        {
            encodage = GL_RGB;
        }
        else
        {
            encodage = GL_BGR;
        }
    }
    else if (imageSDL->format->BytesPerPixel == 4){
        encodageInterne = GL_RGBA;
        if (imageSDL->format->Rmask == 0xff)
        {
            encodage = GL_RGBA;
        }
        else
        {
            encodage = GL_BGRA;
        }
    }
    else
    {
        cout << "Erreur, format interne de l'image inconnu" << endl;
        SDL_FreeSurface(imageSDL);

        return ;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, encodageInterne, imageSDL->w, imageSDL->h, 0, encodage, GL_UNSIGNED_BYTE, imageSDL->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


    glBindTexture(GL_TEXTURE_2D, 0);


    SDL_FreeSurface(imageSDL);
    ------------------------------------------------------------------------------------------------------------------------------*/
    /*-------------------------------------------------------------------------------------------------------------------
    vector<unsigned char> image;
    unsigned width, height;
    unsigned error = lodepng::decode(image, width, height, m_texture_path);

    // If there's an error, display it.
    if(error != 0)
    {
        std::cout << "error " << error << ": " << lodepng_error_text(error) << std::endl;
        return;
    }

    // Texture size must be power of two for the primitive OpenGL version this is written for. Find next power of two.
    size_t u2 = 1;
    while(u2 < width)
    {
        u2 *= 2;
    }

    size_t v2 = 1;
    while(v2 < height)
    {
        v2 *= 2;
    }

    // Ratio for power of two version compared to actual version, to render the non power of two image with proper size.
    double u3 = (double)width / u2;
    double v3 = (double)height / v2;

    // Make power of two version of the image.
    std::vector<unsigned char> image2(u2 * v2 * 4);
    for(size_t y = 0; y < height; y++)
    {
        for(size_t x = 0; x < width; x++)
        {
            for(size_t c = 0; c < 4; c++)
            {
                image2[4 * u2 * y + 4 * x + c] = image[4 * width * y + 4 * x + c];
            }
        }
    }
    cout << "End load png" << endl;
    cout << "Start bind texture" << endl;

    GLuint tex_id;
    glGenTextures(1, &tex_id);

    glBindTexture(GL_TEXTURE_2D, tex_id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    cout << "End bind texture" << endl;

    --------------------------------------------------------------------------------------------------------------------*/
    cout << "End loadTexture()" << endl;
}
