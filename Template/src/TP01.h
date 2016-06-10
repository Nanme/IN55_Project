#ifndef TP01_h
#define TP01_h

#include <ctime>

#include "GlWindow.h"
#include "camera.h"
#include "particlerenderer.h"


class TP01 : public GlWindow
{
private:
    Camera* camera;
    // Variable Used to check if a direction is pushed
    bool isForwardPressed = false;
    bool isLeftPressed = false;
    bool isRightPressed = false;
    bool isDownPressed = false;

    float frameRate = 1.0f/30.0f;
    float cameraSpeed = 20.0f;
    float mouseSensibility = 0.05f;

    Vec2 lastMousePostion;
    clock_t timeStart;
    clock_t timeEnd;
public:
    TP01();
    ~TP01();

    /*!
    *\brief Initialization des objets.
    */
    bool initializeObjects();

    /*!
    *\brief Rendu de la scène.
    */
    void render();

    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};


#endif
