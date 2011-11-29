/* 
 * File:   SGHouse.cpp
 * Author: tom
 * 
 * Created on November 2, 2011, 1:45 PM
 */

#include "SGHouse.h"
#include "SGMatrixTransform.h"
#include "SGSphere.h"
#include "SGCuboid.h"
#include "SGCylinder.h"
#include "Material.h"
#include <algorithm>
#include <iostream>
#include <math.h>
using namespace std;

SGHouse::SGHouse(Material& material, double newSeed) : SGGeode(material) {
  seed = newSeed;
  width = 0;
  house = getHouse();
}

SGHouse::SGHouse(Material& material, double newSeed, double wid) : SGGeode(material) {
  seed = newSeed;
  width = wid;
  house = getHouse();
}

SGHouse::~SGHouse() {
    delete house;
}

void SGHouse::draw(Matrix4 mat) {
    house->draw(mat);
}


SGNode *SGHouse::getHouse() {

    Vector4 ambient(0.2, 0.2, 0.2, 1.0);
    Vector4 diffuse(0.6, 0.6, 0.6, 1.0);
    Vector4 specular(0.2, 0.2, 0.2, 1.0);
    double shininess = 50.0;
    Material material(ambient, diffuse, specular, shininess); 

    if (width == 0)
    {
        width = 15;
    }
    else // adds gap between houses
      width = width - 1;


    double stories = (rand() % 4);
    if (stories == 0)
      stories = 1;

    double height = stories;
    
    // Construct main walls
    Matrix4 houseTransform;
    houseTransform.toTranslationMatrix(0, height/2, 0);

    SGMatrixTransform *house = new SGMatrixTransform(houseTransform);
    houseTransform.toTranslationMatrix(0, 0, 0);

    SGMatrixTransform *mainWallsTransform = new SGMatrixTransform(houseTransform);
    SGCuboid *mainWalls = new SGCuboid(material, width, height, 1);

    mainWallsTransform->addChild(mainWalls);
    house->addChild(mainWallsTransform);

    addRoof(house, width, stories);
    addWindows(house, width, stories);

    if (rand() % 6 == 0)
      addChimney(house, width, stories);

    bool beams = false; // Used for texturing
    if (rand() % 3 == 0)
    {
      addBeams(house, width, stories);
      beams = true;
    }

    if (beams) { // mainwall texture = white

    }
    else { // mainwall texture = something else

    }


    return house;
}

void SGHouse::addWindows(SGMatrixTransform *house, double width, double stories) {
    SGCuboid *window;
    SGMatrixTransform *windowTransform;
    Matrix4 transform;

    Vector4 windowambient(0.5, 0.5, 0.5, 1.0);
    Vector4 windowdiffuse(0.1, 0.1, 0.1, 1.0);
    Vector4 windowspecular(0.1, 0.1, 0.1, 1.0);
    double shininess = 90.0;
    Material windowMat(windowambient, windowdiffuse, windowspecular, shininess); 

    // create windows, top to bottom, left to right
    for (int i = stories; i > 0; --i)
    {
      for (int j = 0; j < width; ++j)
      {
        transform.toTranslationMatrix(j+.5 - width/2, i-.5 - stories/2, .25);
        windowTransform = new SGMatrixTransform(transform);
        window = new SGCuboid(windowMat, .5, .5, 1);
        windowTransform->addChild(window);
        house->addChild(windowTransform);
      }
    }
}

void SGHouse::addRoof(SGMatrixTransform *house, double width, double stories) {
    double roofHeight; // defines pitch of roof
    double angle; // stored in radians
    double roofWidth; // length of one side of roof
    Matrix4 matrix, matrix2, transform; // used in transforming the roof halves

    // pick a random height < .8
    roofHeight = ((double)(rand() % 10)) / 10;
    if (roofHeight > 1/width || roofHeight == 0) // not too tall or zero
      roofHeight = .5;
    
    // calculate angle to rotate roof halves based on roof height
    angle = atan2(roofHeight, width/2);

    // calculate length of roof half
    roofWidth = pow(pow((width / 2), 2) + pow(roofHeight, 2), .5) + 1;
    
    Vector4 ambient(0.2, 0.2, 0.2, 1.0);
    Vector4 diffuse(0.8, 0.8, 0.8, 1.0);
    Vector4 specular(0.2, 0.2, 0.2, 1.0);
    double shininess = 50.0;
    Material material(ambient, diffuse, specular, shininess); 

    /* Left roof */

    SGCuboid *leftRoof = new SGCuboid(material, roofWidth, .1, 1.5);

    // translate pivot to origin
    matrix.toTranslationMatrix((roofWidth/2 - width/2), .05, 0); 
    // rotate
    transform.toRotationMatrixZ(-angle * 180 / 2*acos(0));
    // translate up and over to height 
    matrix2.toTranslationMatrix(width/2, stories, 0);

    matrix2.multiply(transform);
    matrix2.multiply(matrix);

    SGMatrixTransform *leftRoofTransform = new SGMatrixTransform(matrix2);
    leftRoofTransform->addChild(leftRoof);
    

    /* Right roof */

    Vector4 redAmbient(1.0, 0.0, 0.0, 1.0);
    Material redMaterial(redAmbient, diffuse, specular, shininess); 

    SGCuboid *rightRoof = new SGCuboid(redMaterial, roofWidth, .1, 1.5);
    // translate pivot to origin
    matrix.toTranslationMatrix(-(roofWidth/2 - width/2), .05, 0); 
    // rotate
    transform.toRotationMatrixZ(angle * 180 / 2*acos(0));
    // translate up and over to height 
    matrix2.toTranslationMatrix(-width/2, stories, 0);

    matrix2.multiply(transform);
    matrix2.multiply(matrix);

    SGMatrixTransform *rightRoofTransform = new SGMatrixTransform(matrix2);
    rightRoofTransform->addChild(rightRoof);


    house->addChild(leftRoofTransform);
    house->addChild(rightRoofTransform);
}

void SGHouse::addBeams(SGMatrixTransform *house, double width, double stories) {

}

void SGHouse::addChimney(SGMatrixTransform *house, double width, double stories) {

}

