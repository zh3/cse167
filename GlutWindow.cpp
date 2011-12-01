/* 
 * File:   GlutWindow.cpp
 * Author: tom
 * 
 * Created on September 28, 2011, 4:35 PM
 */

#include <iostream>
#include <GL/glut.h>
#include <math.h>
#include <sys/time.h>
#include "GlutWindow.h"
#include "Matrix4.h"
#include "SGNode.h"
#include "SGMatrixTransform.h"

using namespace std;

int GlutWindow::width;
int GlutWindow::height;
Vector3 GlutWindow::prevLocation;
Vector3 GlutWindow::cameraLocation(0.0, 0.0, 10.0);
Vector3 GlutWindow::lookAtPoint(0.0, 0.0, 0.0);
Vector3 GlutWindow::up(0.0, 1.0, 0.0);
Matrix4 GlutWindow::trackballRotation;
Matrix4 GlutWindow::identity;
SGNode *GlutWindow::root;
unsigned int GlutWindow::framesDrawn = 0;
struct timeval GlutWindow::startTime;
Vector3 direction(0,0,10);
bool wPressed = false, aPressed = false, sPressed = false, dPressed = false,
zPressed = false, qPressed = false;

const unsigned int GlutWindow::FRAMERATE_MEASURE_INTERVAL = 100;
const double GlutWindow::FOV = 60.0;
const double GlutWindow::Z_NEAR = 1.0;
const double GlutWindow::Z_FAR = 200.0;

float xpos = 0, ypos = 0, zpos = 0, xrot = 0, yrot = 0, angle=0.0;
void GlutWindow::camera(void) {
    glRotatef(xrot,1.0,0.0,0.0);  //rotate our camera on the x-axis (left and right)
    glRotatef(yrot,0.0,1.0,0.0);  //rotate our camera on the y-axis (up and down)
    glTranslated(-xpos,-ypos,-zpos); //translate the screen to the position of our camera
}

void GlutWindow::idleCallback(void) {

    if (wPressed || aPressed || sPressed || dPressed || qPressed || zPressed) 
      keyboardMovement();

    displayCallback();
}

void GlutWindow::reshapeCallback(int newWidth, int newHeight) {
    width = newWidth;
    height = newHeight;

    // Prevent divide by zero due to improper height
     if (height == 0) {
       height = 1;
    }

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(FOV, (GLfloat) width / (GLfloat) height, Z_NEAR, Z_FAR);

    gluLookAt(cameraLocation.x, cameraLocation.y, cameraLocation.z, 
            lookAtPoint.x, lookAtPoint.y, lookAtPoint.z, up.x, up.y, up.z);
    glMatrixMode(GL_MODELVIEW);
}

void GlutWindow::displayCallback(void) {
     
    
    if (framesDrawn >= FRAMERATE_MEASURE_INTERVAL) {
        double secsPassed;
        double frameRate;
        
        struct timeval currentTime;
        gettimeofday(&currentTime, 0);
        
        secsPassed = currentTime.tv_sec - startTime.tv_sec;
        secsPassed
            += (double) (currentTime.tv_usec - startTime.tv_usec) / 1000000.0;
        frameRate = FRAMERATE_MEASURE_INTERVAL / secsPassed;
        
//        cout << frameRate << " fps" << endl;
        
        framesDrawn = 0;
        gettimeofday(&startTime, 0);
    }
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();  
    camera();
    
    root->draw(identity);

    glFlush();
    glutSwapBuffers();
    
    angle++; //increase the angle
    framesDrawn++;
}

void GlutWindow::keyboardCallback(unsigned char key, int, int)
{
  switch (key)
  {
    case 'w':
      wPressed = true;
      keyboardMovement();
      break;

    case 'a':
      aPressed = true;
      keyboardMovement();
      break;

    case 's':
      sPressed = true;
      keyboardMovement();
      break;

    case 'd':
      dPressed = true;
      keyboardMovement();
      break;
      
    case 'z':
      zPressed = true;
      keyboardMovement();
      break;
      
    case 'q':
      qPressed = true;
      keyboardMovement();
      break;
      
      
  }
}

void GlutWindow::keyboardMovement()
{
  glMatrixMode(GL_MODELVIEW);
  direction.normalize();
  if (wPressed)
  {
    float xrotrad, yrotrad;
    yrotrad = (yrot / 180 * 3.141592654f);
    xrotrad = (xrot / 180 * 3.141592654f);
    xpos += float(sin(yrotrad)) ;
    zpos -= float(cos(yrotrad)) ;
    ypos -= float(sin(xrotrad)) ;
  }
  if (aPressed)
  { yrot -= 1;
    if (yrot < -360)yrot += 360;
  }
  if (sPressed)
  {
    float xrotrad, yrotrad;
    yrotrad = (yrot / 180 * 3.141592654f);
    xrotrad = (xrot / 180 * 3.141592654f);
    xpos -= float(sin(yrotrad));
    zpos += float(cos(yrotrad)) ;
    ypos += float(sin(xrotrad));
  }
  if (dPressed)
  {
    yrot += 1;
    if (yrot >360) yrot -= 360;
  }
  
  if (zPressed) {
    xrot += 1;
    if (xrot >360) xrot -= 360;
  }
  
  if (qPressed) {
    xrot -= 1;
    if (xrot < -360) xrot += 360;
  }
  
  GlutWindow::displayCallback();
}



void GlutWindow::keyboardUpCallback(unsigned char key, int, int) {
  switch (key)
  {
    case 'w':
      wPressed = false;
      break;

    case 'a':
      aPressed = false;
      break;

    case 's':
      sPressed = false;
      break;

    case 'd':
      dPressed = false;
      break;
      
    case 'z':
      zPressed = false;
      break;
      
    case 'q':
      qPressed = false;
      break;
  }
}


void GlutWindow::initializeWindow(int newWidth, int newHeight, int *argc,
    char **argv, string &title) {
    width = newWidth;
    height = newHeight;

    Vector3 prev(width/2,height/2,0);
    prevLocation = prev;

    glutInit(argc, argv);      	      	      // initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
    glutInitWindowSize(width, height);      // set initial window size
    glutCreateWindow(title.c_str());    	      // open window and set window title
    if (glutGet(GLUT_WINDOW_COLORMAP_SIZE) != 0)
    {
       cerr << "Fatal Error: bad RGBA colormap size\n" << endl;
     //  exit(1);
    }

    glEnable(GL_DEPTH_TEST);            	      // enable depth buffering
    glClear(GL_DEPTH_BUFFER_BIT);       	      // clear depth buffer
    glClearColor(0.0, 0.0, 0.0, 0.0);   	      // set clear color to black
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set polygon drawing mode to fill front and back of each polygon
    glShadeModel(GL_SMOOTH);             	      // set shading to smooth

    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_LIGHTING);
    glLoadIdentity();
    // Colors
    glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
    //glEnable ( GL_COLOR_MATERIAL );

    GLfloat pointlight_ambient[] = {0.3, 0.3, 0.3, 1.0};
    GLfloat pointlight_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat pointlight_specular[] = {0.3, 0.3, 0.3, 1.0};
    GLfloat pointlight_position[] = { 0.0, 0.0, 5.0, 1.0 };
    //GLfloat point
    glLightfv(GL_LIGHT0, GL_AMBIENT, pointlight_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, pointlight_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, pointlight_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, pointlight_position);
    
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    
    glEnable(GL_TEXTURE_2D);
    
    identity.toIdentity();
    trackballRotation.toIdentity();
    
    gettimeofday(&startTime, 0);
    // Install callback functions:
    glutDisplayFunc(GlutWindow::displayCallback);
    glutReshapeFunc(GlutWindow::reshapeCallback);
    glutIdleFunc(GlutWindow::idleCallback);
    glutKeyboardFunc(GlutWindow::keyboardCallback);
    glutKeyboardUpFunc(GlutWindow::keyboardUpCallback);
}

void GlutWindow::enterGlutMainLoop(void) {
    glutMainLoop();
}

void GlutWindow::setSceneGraph(SGNode* newRoot) {
    root = newRoot;
}

void GlutWindow::setCamera(const Vector3 &cameraLoc, const Vector3 &lookAt, 
        const Vector3 &upVec) {
    cameraLocation = cameraLoc;
    lookAtPoint = lookAt;
    up = upVec;
}
