
#include <cstdlib>
#include <string>
#include <math.h>
#include "GlutWindow.h"
#include "SGMatrixTransform.h"
#include "SGSphere.h"
#include "SGCuboid.h"
#include "SGCylinder.h"
#include "Material.h"
#include "SGRobot.h"
#include "SGCity.h"

using namespace std;

SGNode *getSceneGraph();
static const double TILE_SIZE = 1.0;
static const double TILE_HEIGHT = 0.05;
static const double ROBOT_HEIGHT = 1.0;


int main(int argc, char** argv) {
/*    Vector3 cam(0.0, 5.0, 5.0);
    Vector3 lookAt(0.0, 0.0, 0.0);
    Vector3 up(0.0, 1.0, 0.0);*/

    Vector3 cam(0.0, 0.0, 0.0);
    Vector3 lookAt(0.0, 0.0, -5.0);
    Vector3 up(0.0, 1.0, 0.0); 

    string name("Procedural World");
    GlutWindow::initializeWindow(512, 512, &argc, argv, name);

    GlutWindow::setCamera(cam, lookAt, up);
    GlutWindow::setSceneGraph(getSceneGraph());
    GlutWindow::enterGlutMainLoop();

    return 0;
}

SGNode *getTiledRobot(Material &limbMaterial, Material &bodyMaterial, 
                      Material &headMaterial, Material &tileMaterial) {
    Matrix4 mat;
    mat.toTranslationMatrix(0.0, -ROBOT_HEIGHT / 2.0, 0.0);
    
    SGRobot *tileRobot = new SGRobot(limbMaterial, bodyMaterial, headMaterial, 
            ROBOT_HEIGHT);
    
    SGCuboid *tile = new SGCuboid(tileMaterial, TILE_SIZE, TILE_HEIGHT, TILE_SIZE);
    SGMatrixTransform *tileTransform = new SGMatrixTransform(mat);
    tileTransform->addChild(tile);
    
    mat.toIdentity();
    SGMatrixTransform *tileBot = new SGMatrixTransform(mat);
    tileBot->addChild(tileTransform);
    tileBot->addChild(tileRobot);
    
    srand(time(NULL));
    SGCity *city = new SGCity(limbMaterial, 100, 100);
    tileBot->addChild(city);
    return tileBot;
}

SGNode *getSceneGraph() {
    Vector4 ambient(0.0, 0.0, 0.2, 1.0);
    Vector4 diffuse(0.0, 0.0, 1.0, 1.0);
    Vector4 specular(1.0, 1.0, 1.0, 1.0);
    double shininess = 50.0;
    Material shinyBlue(ambient, diffuse, specular, shininess); 
    
    ambient.set(0.1, 0.1, 0.1, 1.0);
    diffuse.set(1.0, 1.0, 1.0, 1.0);
    specular.set(1.0, 1.0, 1.0, 1.0);
    Material shinyWhite(ambient, diffuse, specular, shininess);
    
    ambient.set(0.1, 0.1, 0.1, 1.0);
    diffuse.set(0.0, 0.8, 0.0, 1.0);
    specular.set(0.0, 0.0, 0.0, 1.0);
    Material diffuseGreen(ambient, diffuse, specular, shininess);
    
    ambient.set(0.1, 0.0, 0.0, 1.0);
    diffuse.set(1.0, 0.0, 0.0, 1.0);
    specular.set(1.0, 1.0, 1.0, 1.0);
    Material shinyRed(ambient, diffuse, specular, shininess);
    
    return getTiledRobot(shinyWhite, shinyRed, shinyBlue, diffuseGreen);
}

