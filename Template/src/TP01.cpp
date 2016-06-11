#include "TP01.h"


#include "Shapes/Basis.h"
#include "particlerenderer.h"
#include "particlesystem.h"

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

    //cout << "test";
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
        g_particleSystem = new ParticleSystem(this->getCurrentShaderId(), camera);
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

//    cout << "Camera (" << camera->getPosition().x << ", "
//         << camera->getPosition().y
//         << ", " << camera->getPosition().z
//         << ")" << endl;

	// Rendu des objets
    pushMatrix();
        g_particleSystem->update(frameRate);
        g_Basis->draw();
        list<GLMatrix> *L = g_particleSystem->getPart()->getModels();
        for(list<GLMatrix>::iterator i = L->begin(); i != L->end() ; ++i)
        {
            pushMatrix();
                //this->addCustomTransform(g_particleSystem->getPart()->View);
                this->addCustomTransform(*i);
                //GLMatrix tmpMat = g_particleSystem->getPart()->getModel();

                //tmpMat.cout();

                //std::cout << tmpMat;
        //            std::cout << "( " << tmpMat.data[0]  << ", " <<  tmpMat.data[1]  << ", " << tmpMat.data[2]  << ", " << tmpMat.data[3]  << ")" << std::endl;
        //            std::cout << "( " << tmpMat.data[4]  << ", " <<  tmpMat.data[5]  << ", " << tmpMat.data[6]  << ", " << tmpMat.data[7]  << ")" << std::endl;
        //            std::cout << "( " << tmpMat.data[8]  << ", " <<  tmpMat.data[9]  << ", " << tmpMat.data[10] << ", " << tmpMat.data[11] << ")" << std::endl;
        //            std::cout << "( " << tmpMat.data[12] << ", " <<  tmpMat.data[13] << ", " << tmpMat.data[14] << ", " << tmpMat.data[15] << ")" << std::endl;

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
        cout << "isForwardPressed" << endl;
    }
    if(!isLeftPressed && (/*event->key() == Qt::Key_Left || */event->key() == Qt::Key_Q)){
        isLeftPressed = true;
        cout << "isLeftPressed" << endl;
    }
    if(!isRightPressed && (/*event->key() == Qt::Key_Right ||*/ event->key() == Qt::Key_D)){
        isRightPressed = true;
        cout << "isRightPressed" << endl;
    }
    if(!isDownPressed && (/*event->key() == Qt::Key_Down ||*/ event->key() == Qt::Key_S)){
        isDownPressed = true;
        cout << "isDownPressed" << endl;
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
        cout << "isForwardPressed" << endl;
    }
    if(isLeftPressed && (event->key() == Qt::Key_Left || event->key() == Qt::Key_Q)){
        isLeftPressed = false;
        cout << "isLeftPressed" << endl;
    }
    if(isRightPressed && (event->key() == Qt::Key_Right || event->key() == Qt::Key_D)){
        isRightPressed = false;
        cout << "isRightPressed" << endl;
    }
    if(isDownPressed && (event->key() == Qt::Key_Down || event->key() == Qt::Key_S)){
        isDownPressed = false;
        cout << "isDownPressed" << endl;
    }
}
