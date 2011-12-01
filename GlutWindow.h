/* 
 * File:   GlutWindow.h
 * Author: tom
 *
 * Created on September 28, 2011, 4:35 PM
 */

#ifndef GLUTWINDOW_H
#define	GLUTWINDOW_H

#include "Vector3.h"
#include "Matrix4.h"
#include "SGNode.h"
#include "SGMatrixTransform.h"
#include <vector>
#include <string>

typedef SGNode *(*SceneGraphFunction)(void);

class GlutWindow {
public:
    static int width, height;
    static void idleCallback(void);
    static void reshapeCallback(int newWidth, int newHeight);
    static void displayCallback(void);
    static void motionCallback(int x, int y);
    static void mouseCallback(int button, int state, int x, int y);
    static void initializeWindow(int newWidth, int newHeight, int *argc,
        char **argv, std::string &title);
    static void enterGlutMainLoop(void);
    static void setSceneGraphFunction(SceneGraphFunction sgFunction);
    static void setCamera(const Vector3 &cameraLoc, const Vector3 &lookAt, 
                          const Vector3 &upVec);
    static void keyboardCallback(unsigned char key, int, int);
    static void keyboardUpCallback(unsigned char key, int, int);
    static void keyboardMovement();


    
private:
    static Vector3 prevLocation;
    static Matrix4 trackballRotation;
    static Matrix4 identity;
    // Top level node is a transform representing trackball rotation
    static SGNode *root;
    static Vector3 cameraLocation;
    static Vector3 lookAtPoint;
    static Vector3 up;
    static unsigned int framesDrawn;
    static struct timeval startTime;
    static SceneGraphFunction sgFunction;
    
    static const unsigned int FRAMERATE_MEASURE_INTERVAL;
    static const double FOV;
    static const double Z_NEAR;
    static const double Z_FAR;

    static Vector3 getTrackballCoordinates(int windowX, int windowY);
    static void trackballDoRotation(Vector3 newLocation);
    static double getSphereX(int windowX);
    static double getSphereY(int windowY);
    static void camera();
    static void rebuildSceneGraph();
};

#endif	/* GLUTWINDOW_H */

