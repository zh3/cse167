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
#include "Texture.h"
#include "SGTexturedCuboid.h"
using namespace std;

SGHouse::SGHouse(Material& material, double newSeed) : SGGeode(material) {
  seed = newSeed;
  width = 10;
  Texture *textures[1];
  house = getHouse(textures);
}

SGHouse::SGHouse(Material& material, double newSeed, double wid, Texture *tex[]) : SGGeode(material) {
  seed = newSeed;
  width = wid;

/*  textures = new Texture*[11];
  textures[0] = new Texture("./textures/wall1.ppm");
  textures[1] = new Texture("./textures/wall2.ppm");
  textures[2] = new Texture("./textures/wall3.ppm");
  textures[3] = new Texture("./textures/wall4.ppm");
  textures[4] = new Texture("./textures/roof1.ppm");
  textures[5] = new Texture("./textures/roof2.ppm");
  textures[6] = new Texture("./textures/roof3.ppm");
  textures[7] = new Texture("./textures/roof4.ppm");
  textures[8] = new Texture("./textures/beam.ppm");
  textures[9] = new Texture("./textures/wall2.ppm");
  textures[10] = new Texture("./textures/wall3.ppm");
*/

  house = getHouse(tex);
}

SGHouse::~SGHouse() {
    delete house;
}

void SGHouse::draw(Matrix4 mat) {
    house->draw(mat);
}


SGNode *SGHouse::getHouse(Texture *textures[]) {

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
        addBeams(house, width, stories, textures);
        beams = true;
      }
    }


    SGMatrixTransform *mainWallsTransform;
    SGTexturedCuboid *mainWalls;

    int tex = rand() % 4;
    //(textures[rand() % 4])->bindTexture();


    for (int i = 0; i < stories; i++)
    {
      houseTransform.toTranslationMatrix(0, stories/2 - i-.5, 0);

      mainWallsTransform = new SGMatrixTransform(houseTransform);

      if (beams && i == stories - 1)
      {
        if (rand() % 2 == 0)
          mainWalls = new SGTexturedCuboid(material, width-.2, 1, 2-.3, textures[1]);//texture);
        else
          mainWalls = new SGTexturedCuboid(material, width-.2, 1, 2-.3, textures[9]);//texture);
      }

      else if (beams && i < stories - 1)
        mainWalls = new SGTexturedCuboid(material, width, 1, 2, textures[9]);//texture);
      else
        mainWalls = new SGTexturedCuboid(material, width, 1, 2, textures[tex]);//texture);


      mainWallsTransform->addChild(mainWalls);
      house->addChild(mainWallsTransform);
    }

    addRoof(house, width, stories, textures, tex);
    addWindows(house, width, stories, textures);

    if (rand() % 3 == 0)
      addChimney(house, width, stories, textures);

    return house;
}

void SGHouse::addWindows(SGMatrixTransform *house, double width, double stories, Texture *textures[]) {
    SGTexturedCuboid *window;
    SGMatrixTransform *windowTransform;
    Matrix4 transform, transform2;
    double windowWidth, windowHeight;
    int doorPosition;

    Vector4 windowambient(0.8, 0.8, 0.8, 1.0);
    Vector4 windowdiffuse(1.0, 1.0, 1.0, 1.0);
    Vector4 windowspecular(0.5, 0.5, 0.5, 1.0);
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

    int doorTex = 10;//rand() % 2 + 10; // door textures are 10,11
    int windowTex = 11;
    int beamTex = rand() % 2;

    // create windows, top to bottom, left to right
    for (int i = stories; i > 0; --i)
    {
      for (int j = 0; j < width; ++j)
      {
        if (!(i == 1 && j == doorPosition)) // is a window, not a door
        {
          transform.toTranslationMatrix(j+.5 - width/2, i-.5 - stories/2, .05);
          windowTransform = new SGMatrixTransform(transform);
          window = new SGTexturedCuboid(windowMat, windowWidth, windowHeight, 2, textures[windowTex]);
          windowTransform->addChild(window);
          house->addChild(windowTransform);
        }
        else // door
        {
          transform.toTranslationMatrix(j+.5 - width/2, i-.5 - stories/2 - .2, .05);
          windowTransform = new SGMatrixTransform(transform);
          window = new SGTexturedCuboid(windowMat, .5, 1, 2, textures[doorTex]);
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

void SGHouse::addRoof(SGMatrixTransform *house, double width, double stories, Texture* textures[],
  int innerRoofTex) {
    double roofHeight; // defines pitch of roof
    double angle; // stored in radians
    double roofWidth; // length of one side of roof
    Matrix4 matrix, matrix2, transform; // used in transforming the roof halves

/*    // pick a random height < .8
    roofHeight = ((double)(rand() % 10)) / 10;
   // if (roofHeight > 1/width || roofHeight == 0) // not too tall or zero
    //  roofHeight = .5;
    if (roofHeight/width < .1) // stop the angle from being too low relative to width
      roofHeight = .4;

    // calculate angle to rotate roof halves based on roof height
    angle = atan2(roofHeight, (width)/2);
*/
    angle = rand() % 35;
    if (angle < 10)
      angle += 10;

    if (width > 2 && angle > 20)
      angle -= 10;
    if (width == 2 && angle < 25)
      angle += 10;

    angle = angle*2*acos(0)/180;
    roofHeight = 2*tan(angle)/width;

    // calculate length of roof half
    roofWidth = pow(pow((width / 2), 2) + pow(roofHeight, 2), .5) + .7;
    
    Vector4 ambient(0.2, 0.2, 0.2, 1.0);
    Vector4 diffuse(0.6, 0.6, 0.6, 1.0);
    Vector4 specular(0.2, 0.2, 0.2, 1.0);
    double shininess = 50.0;
    Material material(ambient, diffuse, specular, shininess); 

    Vector4 redAmbient(0.5, 0.5, 0.5, 1.0);
    Material redMaterial(redAmbient, diffuse, specular, shininess); 

    // roof textures are 4,5,6,7
    int tex = rand() % 4 + 4;

    /* Left roof */

    SGTexturedCuboid *leftRoof = new SGTexturedCuboid(redMaterial, roofWidth, .1, 2.5, textures[tex]);

    // translate pivot to origin
    matrix.toTranslationMatrix((roofWidth/2 - width/2) - .3, .05, 0); 
    // rotate
    transform.toRotationMatrixZ(-(angle * 180 / (2*acos(0))));
    // translate up and over to height 
    matrix2.toTranslationMatrix(width/2, (stories-.5*stories), 0);//stories*(1-roofHeight), 0);
    
    transform.multiply(matrix);
    matrix2.multiply(transform);

    SGMatrixTransform *leftRoofTransform = new SGMatrixTransform(matrix2);
    leftRoofTransform->addChild(leftRoof);
    

    /* Right roof */


    SGTexturedCuboid *rightRoof = new SGTexturedCuboid(redMaterial, roofWidth, .1, 2.5, textures[tex]);
    // translate pivot to origin
    matrix.toTranslationMatrix(-(roofWidth/2 - width/2) + .3, .05, 0); 
    // rotate
    transform.toRotationMatrixZ(angle * 180 / (2*acos(0)));
    // translate up and over to height 
    matrix2.toTranslationMatrix(-width/2, (stories-.5*stories), 0);//stories*(1-roofHeight), 0);

    matrix2.multiply(transform);
    matrix2.multiply(matrix);

    SGMatrixTransform *rightRoofTransform = new SGMatrixTransform(matrix2);
    rightRoofTransform->addChild(rightRoof);


    /* Inner triangle */
    
    // length of diagonal = width of roof
    SGTexturedCuboid *midRoof = new SGTexturedCuboid(material, pow(.5*pow(width,2), .5), 
      pow(.5*pow(width,2), .5), 1.99, textures[innerRoofTex]);
//    SGCuboid *midRoof = new SGCuboid(material, roofWidth-.7, roofWidth-.7, 1.99);

    matrix.toRotationMatrixZ(-45);
    matrix2.toTranslationMatrix(0, stories-.5*stories, 0); 

    transform.toScalingMatrix(1, roofHeight*width*.5, 1);//roofHeight / (.5 * width), 1);


    // translate up, then rotate, then scale
    transform.multiply(matrix);
    matrix2.multiply(transform);
    //matrix2.multiply(matrix);
    //transform.multiply(matrix2);

    SGMatrixTransform *midRoofTransform = new SGMatrixTransform(matrix2);
    midRoofTransform->addChild(midRoof);
    house->addChild(midRoofTransform);



    house->addChild(leftRoofTransform);
    house->addChild(rightRoofTransform);
}

void SGHouse::addBeams(SGMatrixTransform *house, double width, double stories, Texture *textures[]) {
    Vector4 ambient(0.2, 0.2, 0.2, 1.0);
    Vector4 diffuse(0.2, 0.2, 0.2, 1.0);
    Vector4 specular(0.2, 0.2, 0.2, 1.0);
    double shininess = 50.0;
    Material material(ambient, diffuse, specular, shininess); 

    double storyHeight = 1;
    double beamWidth = .15;
    Matrix4 matrix;
    SGMatrixTransform *beamTransform;
    SGTexturedCuboid *beam;
    
    for (int i = stories; i > 1; --i)
    {
      for (int j = 0; j <= width; ++j)
      {
        matrix.toTranslationMatrix(j - width/2, i-.5 - stories/2, 1.05);
        beamTransform = new SGMatrixTransform(matrix);
        beam = new SGTexturedCuboid(material, beamWidth, storyHeight, .2, textures[8]);
        beamTransform->addChild(beam);
        house->addChild(beamTransform);
      }
      // top beam
      matrix.toTranslationMatrix(0, i - stories/2, 1.05);
      beamTransform = new SGMatrixTransform(matrix);
      beam = new SGTexturedCuboid(material, width, beamWidth, .2, textures[8]);
      beamTransform->addChild(beam);
      house->addChild(beamTransform);

    }
    if (stories > 1)
    {
      // bottom beam
      matrix.toTranslationMatrix(0, 1 - stories/2, 1.05);
      beamTransform = new SGMatrixTransform(matrix);
      beam = new SGTexturedCuboid(material, width, beamWidth, .2, textures[8]);
      beamTransform->addChild(beam);
      house->addChild(beamTransform);
    }


}

void SGHouse::addChimney(SGMatrixTransform *house, double width, double stories, Texture *textures[]) {
    bool onRight = rand() % 2; 
    Matrix4 matrix;
    double chimneyWidth = .5;
    double chimneyHeight = stories + (rand()%10 / 8);

    SGTexturedCuboid *chimney= new SGTexturedCuboid(material, chimneyWidth, chimneyHeight,
                                                    chimneyWidth, textures[1]);
  
    if (onRight)
      matrix.toTranslationMatrix(width/2 - chimneyWidth/2 - .1, stories/2, 0);
    else
      matrix.toTranslationMatrix(-(width/2) + chimneyWidth/2 + .1, stories/2, 0);
    
    // translate up, then rotate, then scale

    SGMatrixTransform *chimneyTransform = new SGMatrixTransform(matrix);
    chimneyTransform->addChild(chimney);

    house->addChild(chimneyTransform);
}

