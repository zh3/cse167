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
  width = 10;
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

    if (width < 2.0)
    {
        width += 3.0;
    }
    else // adds gap between houses
      width = width - 1;

    double stories = (rand() % 4);
    if (stories == 0)
      stories = 1;
    if (stories == 1 && width == 1) // prevent 1x1 houses
      stories = 2;

    double height = stories;

   
    // Construct main walls
    Matrix4 houseTransform;
    houseTransform.toTranslationMatrix(0, height/2, 0);

    SGMatrixTransform *house = new SGMatrixTransform(houseTransform);
    houseTransform.toTranslationMatrix(0, 0, 0);

    bool beams = false; // Used for texturing
    if (stories > 1)
    {
      if (rand() % 2 == 0)
      {
        addBeams(house, width, stories);
        beams = true;
      }
    }


    SGMatrixTransform *mainWallsTransform;
    SGCuboid *mainWalls;
    for (int i = 0; i < stories; i++)
    {
      houseTransform.toTranslationMatrix(0, stories/2 - i-.5, 0);

      mainWallsTransform = new SGMatrixTransform(houseTransform);
      mainWalls = new SGCuboid(material, width, 1, 1);

      if (beams && i == stories - 1)
        mainWalls = new SGCuboid(material, width-.2, 1, 1-.3);

      mainWallsTransform->addChild(mainWalls);
      house->addChild(mainWallsTransform);
    }



    addRoof(house, width, stories);
    addWindows(house, width, stories);

    if (rand() % 3 == 0)
      addChimney(house, width, stories);

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
    double windowWidth, windowHeight;
    int doorPosition;

    Vector4 windowambient(0.5, 0.5, 0.5, 1.0);
    Vector4 windowdiffuse(0.1, 0.1, 0.1, 1.0);
    Vector4 windowspecular(0.1, 0.1, 0.1, 1.0);
    double shininess = 90.0;
    Material windowMat(windowambient, windowdiffuse, windowspecular, shininess); 
    
    windowHeight = (double)(rand() % 8) / 10;
    windowWidth  = (double)(rand() % 8) / 10; 
    if (windowHeight < .2)
      windowHeight += .3;
    if (windowWidth < .2)
      windowWidth += .3;

    // pick a spot for the door
    int wid = (int)width;
    doorPosition = rand() % wid;

    // create windows, top to bottom, left to right
    for (int i = stories; i > 0; --i)
    {
      for (int j = 0; j < width; ++j)
      {
        if (!(i == 1 && j == doorPosition))
        {
          transform.toTranslationMatrix(j+.5 - width/2, i-.5 - stories/2, .25);
          windowTransform = new SGMatrixTransform(transform);
          window = new SGCuboid(windowMat, windowWidth, windowHeight, 1);
          windowTransform->addChild(window);
          house->addChild(windowTransform);
        }
        else
        {
          transform.toTranslationMatrix(j+.5 - width/2, i-.5 - stories/2, .25);
          windowTransform = new SGMatrixTransform(transform);
          window = new SGCuboid(windowMat, windowWidth, 1, 1);
          windowTransform->addChild(window);
          house->addChild(windowTransform);
        }
      }
    }
}

void SGHouse::addSidewaysRoof(SGMatrixTransform *house, double width, double stories) {
    double roofHeight = 1; // defines pitch of roof
    double angle; // stored in radians
    double roofWidth; // length of one side of roof
    Matrix4 matrix, matrix2, transform; // used in transforming the roof halves

    angle = atan2(roofHeight, width/2) - .002;
    roofWidth = pow(pow((width / 2), 2) + pow(roofHeight, 2), .5) + 1;

    Vector4 ambient(0.2, 0.2, 0.2, 1.0);
    Vector4 diffuse(0.6, 0.6, 0.6, 1.0);
    Vector4 specular(0.2, 0.2, 0.2, 1.0);
    double shininess = 50.0;
    Material material(ambient, diffuse, specular, shininess); 

    Vector4 redAmbient(1.0, 0.0, 0.0, 1.0);
    Material redMaterial(redAmbient, diffuse, specular, shininess); 


    /* Left roof */

    SGCuboid *leftRoof = new SGCuboid(redMaterial, roofWidth, .1, width);

    // translate pivot to origin
    matrix.toTranslationMatrix((roofWidth/2 - width/2), .05, 0); 
    // rotate
    transform.toRotationMatrixZ(-angle * 180 / 2*acos(0));
    // translate up and over to height 
    matrix2.toTranslationMatrix(width/2, stories*(1-roofHeight), 0);

    matrix2.multiply(transform);
    matrix2.multiply(matrix);

    SGMatrixTransform *leftRoofTransform = new SGMatrixTransform(matrix2);
    leftRoofTransform->addChild(leftRoof);
    

    /* Right roof */


    SGCuboid *rightRoof = new SGCuboid(redMaterial, roofWidth, .1, 1.5);
    // translate pivot to origin
    matrix.toTranslationMatrix(-(roofWidth/2 - width/2), .05, 0); 
    // rotate
    transform.toRotationMatrixZ(angle * 180 / 2*acos(0));
    // translate up and over to height 
    matrix2.toTranslationMatrix(-width/2, stories*(1-roofHeight), 0);

    matrix2.multiply(transform);
    matrix2.multiply(matrix);

    SGMatrixTransform *rightRoofTransform = new SGMatrixTransform(matrix2);
    rightRoofTransform->addChild(rightRoof);


    /* Inner triangle */

    SGCuboid *midRoof = new SGCuboid(material,pow(.5*pow(width,2), .5), 
      pow(.5*pow(width,2), .5), 1);
  
    matrix.toRotationMatrixZ(45);
    transform.toScalingMatrix(1, roofHeight / (.5 * roofWidth), .99);
    matrix2.toTranslationMatrix(0, stories*(1-roofHeight), 0); 
    
    // translate up, then rotate, then scale
    transform.multiply(matrix);
    matrix2.multiply(transform);

    SGMatrixTransform *midRoofTransform = new SGMatrixTransform(matrix2);
    midRoofTransform->addChild(midRoof);

    house->addChild(midRoofTransform);

    house->addChild(leftRoofTransform);
    house->addChild(rightRoofTransform);


}

void SGHouse::addRoof(SGMatrixTransform *house, double width, double stories) {
    double roofHeight; // defines pitch of roof
    double angle; // stored in radians
    double roofWidth; // length of one side of roof
    Matrix4 matrix, matrix2, transform; // used in transforming the roof halves

    // pick a random height < .8
    roofHeight = ((double)(rand() % 10)) / 10;
   // if (roofHeight > 1/width || roofHeight == 0) // not too tall or zero
    //  roofHeight = .5;
    if (roofHeight/width < .1) // stop the angle from being too low relative to width
      roofHeight = .4;

    // calculate angle to rotate roof halves based on roof height
    angle = atan2(roofHeight, width/2);

    // calculate length of roof half
    roofWidth = pow(pow((width / 2), 2) + pow(roofHeight, 2), .5) + .5;
    
    Vector4 ambient(0.2, 0.2, 0.2, 1.0);
    Vector4 diffuse(0.6, 0.6, 0.6, 1.0);
    Vector4 specular(0.2, 0.2, 0.2, 1.0);
    double shininess = 50.0;
    Material material(ambient, diffuse, specular, shininess); 

    Vector4 redAmbient(1.0, 0.0, 0.0, 1.0);
    Material redMaterial(redAmbient, diffuse, specular, shininess); 

    /* Left roof */

    SGCuboid *leftRoof = new SGCuboid(redMaterial, roofWidth, .1, 1.5);

    // translate pivot to origin
    matrix.toTranslationMatrix((roofWidth/2 - width/2), .05, 0); 
    // rotate
    transform.toRotationMatrixZ(-angle * 180 / 2*acos(0));
    // translate up and over to height 
    matrix2.toTranslationMatrix(width/2, stories*(1-roofHeight), 0);

    matrix2.multiply(transform);
    matrix2.multiply(matrix);

    SGMatrixTransform *leftRoofTransform = new SGMatrixTransform(matrix2);
    leftRoofTransform->addChild(leftRoof);
    

    /* Right roof */


    SGCuboid *rightRoof = new SGCuboid(redMaterial, roofWidth, .1, 1.5);
    // translate pivot to origin
    matrix.toTranslationMatrix(-(roofWidth/2 - width/2), .05, 0); 
    // rotate
    transform.toRotationMatrixZ(angle * 180 / 2*acos(0));
    // translate up and over to height 
    matrix2.toTranslationMatrix(-width/2, stories*(1-roofHeight), 0);

    matrix2.multiply(transform);
    matrix2.multiply(matrix);

    SGMatrixTransform *rightRoofTransform = new SGMatrixTransform(matrix2);
    rightRoofTransform->addChild(rightRoof);


    /* Inner triangle */

    SGCuboid *midRoof = new SGCuboid(material, pow(.5*pow(width,2), .5), 
      pow(.5*pow(width,2), .5), 1);
  
    matrix.toRotationMatrixZ(45);
    transform.toScalingMatrix(1, roofHeight / (.5 * width), .99);
    matrix2.toTranslationMatrix(0, stories*(1-roofHeight), 0); 
    
    // translate up, then rotate, then scale
    transform.multiply(matrix);
    matrix2.multiply(transform);

    SGMatrixTransform *midRoofTransform = new SGMatrixTransform(matrix2);
    midRoofTransform->addChild(midRoof);

    house->addChild(midRoofTransform);

    house->addChild(leftRoofTransform);
    house->addChild(rightRoofTransform);
}

void SGHouse::addBeams(SGMatrixTransform *house, double width, double stories) {
    Vector4 ambient(0.2, 0.2, 0.2, 1.0);
    Vector4 diffuse(0.2, 0.2, 0.2, 1.0);
    Vector4 specular(0.2, 0.2, 0.2, 1.0);
    double shininess = 50.0;
    Material material(ambient, diffuse, specular, shininess); 

    double storyHeight = 1;
    double beamWidth = .15;
    Matrix4 matrix;
    SGMatrixTransform *beamTransform;
    SGCuboid *beam;
    
    for (int i = stories; i > 1; --i)
    {
      for (int j = 0; j <= width; ++j)
      {
        matrix.toTranslationMatrix(j - width/2, i-.5 - stories/2, .1);
        beamTransform = new SGMatrixTransform(matrix);
        beam = new SGCuboid(material, beamWidth, storyHeight, .99);
        beamTransform->addChild(beam);
        house->addChild(beamTransform);
      }
      // top beam
      matrix.toTranslationMatrix(0, i - stories/2, 0);
      beamTransform = new SGMatrixTransform(matrix);
      beam = new SGCuboid(material, width, beamWidth, 1.1);
      beamTransform->addChild(beam);
      house->addChild(beamTransform);

    }
    if (stories > 1)
    {
      // bottom beam
      matrix.toTranslationMatrix(0, 1 - stories/2, 0);
      beamTransform = new SGMatrixTransform(matrix);
      beam = new SGCuboid(material, width, beamWidth, 1.1);
      beamTransform->addChild(beam);
      house->addChild(beamTransform);
    }


}

void SGHouse::addChimney(SGMatrixTransform *house, double width, double stories) {
    bool onRight = rand() % 2; 
    Matrix4 matrix;
    double chimneyWidth = .5;
    double chimneyHeight = stories + (rand()%10 / 8);

    SGCuboid *chimney= new SGCuboid(material, chimneyWidth, chimneyHeight, chimneyWidth);
  
    if (onRight)
      matrix.toTranslationMatrix(width/2 - chimneyWidth/2, stories/2, 0);
    else
      matrix.toTranslationMatrix(-(width/2) + chimneyWidth/2, stories/2, 0);
    
    // translate up, then rotate, then scale

    SGMatrixTransform *chimneyTransform = new SGMatrixTransform(matrix);
    chimneyTransform->addChild(chimney);

    house->addChild(chimneyTransform);
}

