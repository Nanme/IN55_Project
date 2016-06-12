#include "TP01.h"


#include "Shapes/Basis.h"
#include "particlerenderer.h"
#include "particlesystem.h"
#include "coneemitter.h"

#include <iostream>
#include <cmath>
#include <unistd.h>

using namespace std;


GLfloat angle1 = 30.0f;
GLfloat angle2 = 20.0f;

GLfloat angle = 0.0f;

const GLfloat g_AngleSpeed = 10.0f;


Basis* g_Basis;
//ParticleRenderer* g_particle;
ParticleSystem* g_particleSystem;
GLuint g_CameraRight_worldspace_ID;
GLuint g_CameraUp_worldspace_ID;
GLuint g_ViewProjMatrixID;

TP01::TP01()
{
	setWindowTitle(trUtf8("IN55-TP01"));

    g_Basis = new Basis( 10.0 );

    camera = new Camera(0.0f, 5.0f, 30.0f, 4.0f/3.0f, 0.3f, 1000.0f, 60.0f);
    timeStart = clock();

    QCursor::setPos(this->geometry().x() + (this->geometry().width() / 2.0f),
                    this->geometry().y() + (this->geometry().height() / 2.0f) );
    lastMousePostion = Vec2((float)QCursor::pos().x(), (float)QCursor::pos().y());

}


TP01::~TP01()
{
    delete g_Basis;
    delete g_particleSystem;
    delete camera;
}


bool
TP01::initializeObjects()
{
	// Fond gris
	glClearColor( 0.2f, 0.2f, 0.2f, 1.0f );
	glEnable( GL_DEPTH_TEST );

	// Chargement des shaders
	createShader( "Shaders/color" );

    cout << "Shader color: ";
    if (useShader( "color" ))
    {
        cout << "Loaded!" << endl;
//        g_particle = new ParticleRenderer("tex2d_pikachu.png", this->getCurrentShaderId());
        g_particleSystem = new ParticleSystem(this->getCurrentShaderId(), camera, new ConeEmitter(1.0f, 3.0f, 10.0f, 3.0f, 1000));
    }
    else
    {
        cout << "NOT Loaded!" << endl;
    }
	return true;
}


void
TP01::render()
{

    timeStart = clock();

	// Initialisation de la caméra
//	lookAt( 0, 5, 30, 0, 0, 0 );

    pViewMatrix = camera->getViewMatrix();
    pProjMatrix = camera->getProjectionMatrix();

    if(isForwardPressed) {
        camera->translateZ(cameraSpeed * frameRate);
    }
    if(isRightPressed)
        camera->translateX(-cameraSpeed * frameRate);
    if(isLeftPressed)
        camera->translateX(cameraSpeed * frameRate);
    if(isDownPressed)
        camera->translateZ(-cameraSpeed * frameRate);

    Vec2 currentMousePosition;
    if(this->geometry().contains(QCursor::pos()))
        currentMousePosition = Vec2((float)QCursor::pos().x(), (float)QCursor::pos().y());
    else
        currentMousePosition = lastMousePostion;

    float mDirx = lastMousePostion.x - currentMousePosition.x;
    float mDiry = lastMousePostion.y - currentMousePosition.y;

    camera->rotateX(mDiry * mouseSensibility * frameRate);
    camera->rotateY(mDirx * mouseSensibility * frameRate);

    lastMousePostion = currentMousePosition;


    pViewMatrix = camera->getViewMatrix();
    pProjMatrix = camera->getProjectionMatrix();

	// Rendu des objets
    pushMatrix();
        g_particleSystem->update(frameRate);
        g_Basis->draw();
        list<GLMatrix> *L = g_particleSystem->getPart()->getModels();
        for(list<GLMatrix>::iterator i = L->begin(); i != L->end() ; ++i)
        {
            pushMatrix();
                //this->addCustomTransform(g_particleSystem->getPart()->View)
                this->addCustomTransform(*i);
                g_particleSystem->getRenderer()->draw();
            popMatrix();

        }
      //  g_Basis->draw();
	popMatrix();    


    timeEnd = clock();
    clock_t frameTime = timeEnd - timeStart;
    float framefTime = ((float)frameTime) / CLOCKS_PER_SEC;

    if(framefTime < frameRate)
        usleep((frameRate - framefTime) * 1000000);

    delete L;
}


void TP01::mouseMoveEvent(QMouseEvent *event){
    cout << "YEY SOURIS : " << event->globalX() << " " << event->globalY() << endl;
}

void
TP01::keyPressEvent( QKeyEvent* event )
{

    if(!isForwardPressed && (/*event->key() == Qt::Key_Up ||*/ event->key() == Qt::Key_Z)){
        isForwardPressed = true;
    }
    if(!isLeftPressed && (/*event->key() == Qt::Key_Left || */event->key() == Qt::Key_Q)){
        isLeftPressed = true;
    }
    if(!isRightPressed && (/*event->key() == Qt::Key_Right ||*/ event->key() == Qt::Key_D)){
        isRightPressed = true;
    }
    if(!isDownPressed && (/*event->key() == Qt::Key_Down ||*/ event->key() == Qt::Key_S)){
        isDownPressed = true;
    }
    if(event->key() == Qt::Key_Escape)
        this->close();
    if(event->key() == Qt::Key_G)
        camera->rotateY(M_PI / 2.0f);
//    switch( event->key())
//	{
//		case Qt::Key_Escape:
//			close();
//			break;

//		case Qt::Key_Left:
//            camera->translateX(0.1f);
//			angle1 -= g_AngleSpeed;
//			break;

//		case Qt::Key_Right:
//            camera->translateX(-0.1f);
//			angle1 += g_AngleSpeed;
//			break;

//		case Qt::Key_Up:
//            camera->rotateX(M_PI/4.0f);
//			angle2 -= g_AngleSpeed;
//			break;

//		case Qt::Key_Down:
//            camera->rotateX(-M_PI/4.0f);
//			angle2 += g_AngleSpeed;
//			break;

//		case Qt::Key_R:
//			angle1 = angle2 = 0.0f;
//			break;
    }

void TP01::keyReleaseEvent(QKeyEvent *event){
    if(isForwardPressed && (event->key() == Qt::Key_Up || event->key() == Qt::Key_Z)){
        isForwardPressed = false;
    }
    if(isLeftPressed && (event->key() == Qt::Key_Left || event->key() == Qt::Key_Q)){
        isLeftPressed = false;
    }
    if(isRightPressed && (event->key() == Qt::Key_Right || event->key() == Qt::Key_D)){
        isRightPressed = false;
    }
    if(isDownPressed && (event->key() == Qt::Key_Down || event->key() == Qt::Key_S)){
        isDownPressed = false;
    }
}
