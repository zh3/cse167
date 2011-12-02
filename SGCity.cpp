/* 
 * File:   SGCity.cpp
 * Author: Cathy
 * 
 * Created on November 22, 2011
 */

#include "SGCity.h"
#include "SGCity.h"
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
#include "SGTexturedPlane.h"
#include "SGTexturedCuboid.h"
#include "SGLSystem.h"
#include "DrawSegmentAction.h"
#include "DrawSegmentMaterialAction.h"

using namespace std;

SGCity::SGCity(Material& material, double newSeed, double newBlockWidth) : SGGeode(material) {
  seed = newSeed;
  
  // door = 7,8,10
  // window = 11
  // chimney = 1
  textures[0] = new Texture("./textures/wall1.ppm");
  textures[1] = new Texture("./textures/brick1.ppm");
  textures[2] = new Texture("./textures/wall3.ppm");
  textures[3] = new Texture("./textures/wall4.ppm");

  textures[4] = new Texture("./textures/roof1.ppm");
  textures[5] = new Texture("./textures/roof2.ppm");
  textures[6] = new Texture("./textures/brick3.ppm");
  textures[7] = new Texture("./textures/roof4.ppm");

  textures[8] = new Texture("./textures/beam.ppm");
  textures[9] = new Texture("./textures/plaster.ppm");
  textures[10] = new Texture("./textures/door4.ppm");
  textures[11] = new Texture("./textures/window2.ppm");
 // textures[12] = new Texture("./textures/door2.ppm");
//  textures[13] = new Texture("./textures/door3.ppm");
//  textures[14] = new Texture("./textures/wall3.ppm");

  city = getCity();
}

SGCity::~SGCity() {
    delete city;
}

void SGCity::draw(Matrix4 mat) {
    city->draw(mat);
}

SGNode *SGCity::getCity() {
    Vector4 ambient(0.5, 0.5, 0.5, 1.0);
    Vector4 diffuse(0.8, 0.8, 0.8, 1.0);
    Vector4 specular(0.2, 0.2, 0.2, 1.0);
    double shininess = 50.0;
    Material material(ambient, diffuse, specular, shininess); 

    // set up city
    Matrix4 cityTransform, blockTransform, blockTranslateMatrix;
    cityTransform.toTranslationMatrix(0, 0, 0);

    SGMatrixTransform *city = new SGMatrixTransform(cityTransform);
    SGMatrixTransform *block;

    // right block
    blockTransform.toRotationMatrixY(90);
    blockTranslateMatrix.toTranslationMatrix(-50, 0, 0);
    block = getBlock(100);
    blockTranslateMatrix.multiply(blockTransform);
    block->setTransformationMatrix(blockTranslateMatrix);
    city->addChild(block);


    blockTranslateMatrix.toTranslationMatrix(-25, 0, -24);
    block = getBlock(45);
    blockTranslateMatrix.multiply(blockTransform);
    block->setTransformationMatrix(blockTranslateMatrix);
    city->addChild(block);

    blockTranslateMatrix.toTranslationMatrix(-25, 0, 24);
    block = getBlock(45);
    blockTranslateMatrix.multiply(blockTransform);
    block->setTransformationMatrix(blockTranslateMatrix);
    city->addChild(block);


    blockTransform.toRotationMatrixY(-90);
    blockTranslateMatrix.toTranslationMatrix(-28, 0, -24);
    block = getBlock(45);
    blockTranslateMatrix.multiply(blockTransform);
    block->setTransformationMatrix(blockTranslateMatrix);
    city->addChild(block);

    blockTranslateMatrix.toTranslationMatrix(-28, 0, 24);
    block = getBlock(45);
    blockTranslateMatrix.multiply(blockTransform);
    block->setTransformationMatrix(blockTranslateMatrix);
    city->addChild(block);


    // bottom block
    blockTransform.toRotationMatrixY(180);
    blockTranslateMatrix.toTranslationMatrix(0, 0, 50);
    block = getBlock(95);
    blockTranslateMatrix.multiply(blockTransform);
    block->setTransformationMatrix(blockTranslateMatrix);
    city->addChild(block);   

/*
    blockTransform.toRotationMatrixY(0);
    blockTranslateMatrix.toTranslationMatrix(30, 0, 20);
    block = getBlock(11);
    blockTranslateMatrix.multiply(blockTransform);
    block->setTransformationMatrix(blockTranslateMatrix);
    city->addChild(block);

    blockTranslateMatrix.toTranslationMatrix(44, 0, 20);
    block = getBlock(11);
    blockTranslateMatrix.multiply(blockTransform);
    block->setTransformationMatrix(blockTranslateMatrix);
    city->addChild(block);
*/
    // left block
    blockTransform.toRotationMatrixY(270);
    blockTranslateMatrix.toTranslationMatrix(50, 0, 0);
    block = getBlock(100);
    blockTranslateMatrix.multiply(blockTransform);
    block->setTransformationMatrix(blockTranslateMatrix);
    city->addChild(block);


    blockTranslateMatrix.toTranslationMatrix(25, 0, -24);
    block = getBlock(45);
    blockTranslateMatrix.multiply(blockTransform);
    block->setTransformationMatrix(blockTranslateMatrix);
    city->addChild(block);

    blockTranslateMatrix.toTranslationMatrix(25, 0, 24);
    block = getBlock(45);
    blockTranslateMatrix.multiply(blockTransform);
    block->setTransformationMatrix(blockTranslateMatrix);
    city->addChild(block);

    blockTransform.toRotationMatrixY(-270);
    blockTranslateMatrix.toTranslationMatrix(28, 0, -24);
    block = getBlock(45);
    blockTranslateMatrix.multiply(blockTransform);
    block->setTransformationMatrix(blockTranslateMatrix);
    city->addChild(block);

    blockTranslateMatrix.toTranslationMatrix(28, 0, 24);
    block = getBlock(45);
    blockTranslateMatrix.multiply(blockTransform);
    block->setTransformationMatrix(blockTranslateMatrix);
    city->addChild(block);



    // top block
    blockTransform.toRotationMatrixY(0);
    blockTranslateMatrix.toTranslationMatrix(0, 0, -50);
    block = getBlock(95);
    blockTranslateMatrix.multiply(blockTransform);
    block->setTransformationMatrix(blockTranslateMatrix);
    city->addChild(block);

    // skybox
    Texture *texture;
    SGTexturedPlane *plane;
    SGMatrixTransform *transform;
    Matrix4 matrix, matrix2;

    // paths
    Vector4 skyboxambient(1.0, 1.0, 1.0, 1.0);
    Vector4 skyboxdiffuse(0.0, 0.0, 0.0, 1.0);
    Vector4 skyboxspecular(0.0, 0.0, 0.0, 1.0);
    double skyboxshininess = 50.0;
    Material skyboxmaterial(skyboxambient, skyboxdiffuse, skyboxspecular, skyboxshininess); 

    SGTexturedCuboid *wall;

    texture = new Texture("./textures/brick3.ppm");
    wall = new SGTexturedCuboid(skyboxmaterial, 2.5, .5, 105, texture);

    matrix.toTranslationMatrix(0, -.2, 0);
    matrix2.toRotationMatrixY(90);
    matrix.multiply(matrix2);

    transform = new SGMatrixTransform(matrix);
    transform->addChild(wall);
    city->addChild(transform);

//    wall = new SGTexturedCuboid(skyboxmaterial, 1, .5, 90, texture);
    
    // left center vertical
    matrix.toTranslationMatrix(-23, -.2, 0);
    transform = new SGMatrixTransform(matrix);
    transform->addChild(wall);
    city->addChild(transform);

    // lefter vertical
    matrix.toTranslationMatrix(-29.5, -.2, 0);
    transform = new SGMatrixTransform(matrix);
    transform->addChild(wall);
    city->addChild(transform);

    // leftest vertical
    matrix.toTranslationMatrix(-48, -.2, 0);
    transform = new SGMatrixTransform(matrix);
    transform->addChild(wall);
    city->addChild(transform);

    // right center vertical
    matrix.toTranslationMatrix(23, -.2, 0);
    transform = new SGMatrixTransform(matrix);
    transform->addChild(wall);
    city->addChild(transform);

    // righter vertical
    matrix.toTranslationMatrix(29.5, -.2, 0);
    transform = new SGMatrixTransform(matrix);
    transform->addChild(wall);
    city->addChild(transform);

    // rightest vertical
    matrix.toTranslationMatrix(48, -.2, 0);
    transform = new SGMatrixTransform(matrix);
    transform->addChild(wall);
    city->addChild(transform);



    // top horizontal
    matrix.toTranslationMatrix(0, -.2, -48);
    matrix2.toRotationMatrixY(90);
    matrix.multiply(matrix2);
    transform = new SGMatrixTransform(matrix);
    transform->addChild(wall);
    city->addChild(transform);

    // bottom horizontal
    matrix.toTranslationMatrix(0, -.2, 48);
    matrix2.toRotationMatrixY(90);
    matrix.multiply(matrix2);
    transform = new SGMatrixTransform(matrix);
    transform->addChild(wall);
    city->addChild(transform);

    // floor
    texture = new Texture("./textures/grass.ppm");
    plane = new SGTexturedPlane(material, texture, 1, 1, 10);
    
    matrix.toRotationMatrixX(-90);
    matrix2.toScalingMatrix(120,120,4);
    matrix.multiply(matrix2);
    transform = new SGMatrixTransform(matrix);
    transform->addChild(plane);
    city->addChild(transform);


    // front
    texture = new Texture("./textures/skyboxFrontFlipped.ppm");
    plane = new SGTexturedPlane(skyboxmaterial, texture, 1, 1, 1);

    matrix.toTranslationMatrix(0, 10, -60);
    matrix2.toScalingMatrix(120,120,1);
    matrix.multiply(matrix2);
    matrix2.toRotationMatrixX(180);
    matrix.multiply(matrix2);

    matrix2.toRotationMatrixZ(180);
    matrix.multiply(matrix2);
    matrix2.toRotationMatrixY(-180);
    matrix.multiply(matrix2);

    matrix2.toRotationMatrixX(-180);
    matrix.multiply(matrix2);
    matrix2.toRotationMatrixY(-180);
    matrix.multiply(matrix2);

    transform = new SGMatrixTransform(matrix);
    transform->addChild(plane);
    city->addChild(transform);

    // back
    texture = new Texture("./textures/skyboxBackFlipped.ppm");
    plane = new SGTexturedPlane(skyboxmaterial, texture, 1, 1, 1);

    matrix.toTranslationMatrix(0, 10, 60);
    matrix2.toScalingMatrix(120,120,1);
    matrix.multiply(matrix2);
    matrix2.toRotationMatrixZ(180);
//    matrix.multiply(matrix2);
    matrix2.toRotationMatrixX(-180);
    matrix.multiply(matrix2);


    transform = new SGMatrixTransform(matrix);
    transform->addChild(plane);
    city->addChild(transform);

    // left
    texture = new Texture("./textures/skyboxLeftFlipped.ppm");
    plane = new SGTexturedPlane(skyboxmaterial, texture, 1, 1, 1);

    matrix.toTranslationMatrix(-60, 10, 0);
    matrix2.toRotationMatrixY(90);
    matrix.multiply(matrix2);

    matrix2.toScalingMatrix(120,120,1);
    matrix.multiply(matrix2);

    matrix2.toRotationMatrixY(180);
    matrix.multiply(matrix2);

    matrix2.toRotationMatrixX(180);
    matrix.multiply(matrix2);
    matrix2.toRotationMatrixZ(180);
    //matrix.multiply(matrix2);
    matrix2.toRotationMatrixY(180);
    //matrix.multiply(matrix2); 

    transform = new SGMatrixTransform(matrix);
    transform->addChild(plane);
    city->addChild(transform);

    // right
    texture = new Texture("./textures/skyboxRightFlipped.ppm");
    plane = new SGTexturedPlane(skyboxmaterial, texture, 1, 1, 1);

    matrix.toTranslationMatrix(60, 10, 0);
    matrix2.toRotationMatrixY(90);
    matrix.multiply(matrix2);
    matrix2.toScalingMatrix(120,120,1);
    matrix.multiply(matrix2);
    matrix2.toRotationMatrixX(180);
    matrix.multiply(matrix2);
    matrix2.toRotationMatrixY(-180);
    matrix.multiply(matrix2);

    matrix2.toRotationMatrixY(180);
    matrix.multiply(matrix2);

    transform = new SGMatrixTransform(matrix);
    transform->addChild(plane);
    city->addChild(transform);

    // top  
    texture = new Texture("./textures/skyboxTopFlipped.ppm");
    plane = new SGTexturedPlane(skyboxmaterial, texture, 1, 1, 1);

    matrix.toTranslationMatrix(0, 65, 0);

    matrix2.toRotationMatrixX(-90);
    matrix.multiply(matrix2);

    matrix2.toScalingMatrix(120,120,1);
    matrix.multiply(matrix2);

    matrix2.toRotationMatrixX(180);
    matrix.multiply(matrix2);
    matrix2.toRotationMatrixZ(180);
    matrix.multiply(matrix2);

    transform = new SGMatrixTransform(matrix);
    transform->addChild(plane);
    city->addChild(transform);

    // front wall 
    texture = new Texture("./textures/wall4.ppm");
    wall = new SGTexturedCuboid(skyboxmaterial, 105, 7, 1, texture);

    matrix.toTranslationMatrix(0, 0, -55);
    //matrix.multiply(matrix2);

    transform = new SGMatrixTransform(matrix);
    transform->addChild(wall);
    city->addChild(transform);

    // back wall 
    texture = new Texture("./textures/wall4.ppm");
    wall = new SGTexturedCuboid(skyboxmaterial, 105, 7, 1, texture);

    matrix.toTranslationMatrix(0, 0, 55);
    //matrix.multiply(matrix2);

    transform = new SGMatrixTransform(matrix);
    transform->addChild(wall);
    city->addChild(transform);

    // right wall 
    texture = new Texture("./textures/wall4.ppm");
    wall = new SGTexturedCuboid(skyboxmaterial, 105, 7, 1, texture);

    matrix2.toRotationMatrixY(90);
    matrix.toTranslationMatrix(55, 0, 0);
    matrix.multiply(matrix2);


    transform = new SGMatrixTransform(matrix);
    transform->addChild(wall);
    city->addChild(transform);

    // left wall 
    texture = new Texture("./textures/wall4.ppm");
    wall = new SGTexturedCuboid(skyboxmaterial, 105, 7, 1, texture);

    matrix2.toRotationMatrixY(90);
    matrix.toTranslationMatrix(-55, 0, 0);
    matrix.multiply(matrix2);


    transform = new SGMatrixTransform(matrix);
    transform->addChild(wall);
    city->addChild(transform);

    block = getFountain();
    city->addChild(block);

    // bottom left
    block = getBench();
    matrix.toTranslationMatrix(-7, 0, 7);
    matrix2.toRotationMatrixY(-45);
    matrix.multiply(matrix2);
    matrix2.toScalingMatrix(2,2,2);
    matrix.multiply(matrix2);
    transform = new SGMatrixTransform(matrix);
    transform->addChild(block);
    city->addChild(transform);

    // bottom right 
    block = getBench();
    matrix.toTranslationMatrix(7, 0, 7);
    matrix2.toRotationMatrixY(45);
    matrix.multiply(matrix2);
    matrix2.toScalingMatrix(2,2,2);
    matrix.multiply(matrix2);
    transform = new SGMatrixTransform(matrix);
    transform->addChild(block);
    city->addChild(transform);

    // top left 
    block = getBench();
    matrix.toTranslationMatrix(-7, 0, -7);
    matrix2.toRotationMatrixY(-90-45);
    matrix.multiply(matrix2);
    matrix2.toScalingMatrix(2,2,2);
    matrix.multiply(matrix2);
    transform = new SGMatrixTransform(matrix);
    transform->addChild(block);
    city->addChild(transform);

    // top right 
    block = getBench();
    matrix.toTranslationMatrix(7, 0, -7);
    matrix2.toRotationMatrixY(90+45);
    matrix.multiply(matrix2);
    matrix2.toScalingMatrix(2,2,2);
    matrix.multiply(matrix2);
    transform = new SGMatrixTransform(matrix);
    transform->addChild(block);
    city->addChild(transform);


    return city;
}

SGMatrixTransform *SGCity::getFountain()
{
  Vector4 ambient(0.5, 0.5, 0.5, 1.0);
  Vector4 diffuse(0.5, 0.5, 0.5, 1.0);
  Vector4 specular(.2, .2, .2, 1.0);
  double shininess = 1.0;
  Material fountainMat(ambient, diffuse, specular, shininess); 

  SGCylinder *cylinder;
  Matrix4 matrix, matrix2;
  SGMatrixTransform *transform, *fountain;
  matrix.toIdentity();
  fountain = new SGMatrixTransform(matrix);

  // base
  cylinder = new SGCylinder(fountainMat, 3, 1.5);
  matrix.toTranslationMatrix(0,0,0);
  
  transform = new SGMatrixTransform(matrix);
  transform->addChild(cylinder);
  fountain->addChild(transform);

  // center pole
  cylinder = new SGCylinder(fountainMat, .2, 9);
  matrix.toTranslationMatrix(0,0,0);
  
  transform = new SGMatrixTransform(matrix);
  transform->addChild(cylinder);
  fountain->addChild(transform);

  // middle
  cylinder = new SGCylinder(fountainMat, 2, .5);
  matrix.toTranslationMatrix(0,2.25,0);
  
  transform = new SGMatrixTransform(matrix);
  transform->addChild(cylinder);
  fountain->addChild(transform);

  // top
  cylinder = new SGCylinder(fountainMat, 1, .5);
  matrix.toTranslationMatrix(0,4,0);
  
  transform = new SGMatrixTransform(matrix);
  transform->addChild(cylinder);
  fountain->addChild(transform);

  SGNode *water = getWater();
  matrix.toTranslationMatrix(0,4,0);
  matrix2.toScalingMatrix(1,1,1);
  matrix.multiply(matrix2);
  transform = new SGMatrixTransform(matrix);
  transform->addChild(water);
  fountain->addChild(transform);

  return fountain;
}

SGMatrixTransform *SGCity::getBench()
{
  Vector4 ambient(0.4, 0.2, 0.1, 1.0);
  Vector4 diffuse(0.4, 0.2, 0.1, 1.0);
  Vector4 specular(.4, .2, .2, 1.0);
  double shininess = 50.0;
  Material benchMat(ambient, diffuse, specular, shininess); 

  SGCuboid *cube;
  Matrix4 matrix, matrix2;
  SGMatrixTransform *transform, *bench;
  matrix.toIdentity();
  bench = new SGMatrixTransform(matrix);
  
  // seat
  cube = new SGCuboid(benchMat, 1, .2, .5);//, textures[10]);
  matrix.toTranslationMatrix(0, .3, -.15);
  transform = new SGMatrixTransform(matrix);
  transform->addChild(cube);
  bench->addChild(transform);
  
  // back
  cube = new SGCuboid(benchMat, 1, .2, .5);//, textures[10]);
  matrix.toTranslationMatrix(0, .5, 0);
  matrix2.toRotationMatrixX(90);
  matrix.multiply(matrix2);
  transform = new SGMatrixTransform(matrix);
  transform->addChild(cube);
  bench->addChild(transform);

  // feet 
  cube = new SGCuboid(benchMat, .1, .5, .1);//, textures[10]);
  
  matrix.toTranslationMatrix(.3, 0, -.3);
  transform = new SGMatrixTransform(matrix);
  transform->addChild(cube);
  bench->addChild(transform);

  matrix.toTranslationMatrix(-.3, 0, -.3);
  transform = new SGMatrixTransform(matrix);
  transform->addChild(cube);
  bench->addChild(transform);

  matrix.toTranslationMatrix(.3, 0, 0);
  transform = new SGMatrixTransform(matrix);
  transform->addChild(cube);
  bench->addChild(transform);

  matrix.toTranslationMatrix(-.3, 0, 0);
  transform = new SGMatrixTransform(matrix);
  transform->addChild(cube);
  bench->addChild(transform);

//  return new SGMatrixTransform();
  return bench;
}

SGNode *SGCity::getWater()
{
    Vector4 ambient(0.2, 0.2, 0.8, 1.0);
    Vector4 diffuse(0.2, 0.2, 1.0, 1.0);
    Vector4 specular(1.0, 1.0, 1.0, 1.0);
    double shininess = 50.0;
    Material shinyBlue(ambient, diffuse, specular, shininess); 

    multimap<char, LSystemRule*> *rules = new multimap<char, LSystemRule*>();
    map<char, TurtleAction*> *variableActions = new map<char, TurtleAction*>();
    string base("F");
    string ruleF1("F[+&<F+&<F-<&F][>>F]");
    rules->insert(pair<char, LSystemRule*>('F', new LSystemRule(ruleF1, .7)));

    string ruleF2(">>F[>>&F][>>&F][>>&F][>>>>&F]");
    rules->insert(pair<char, LSystemRule*>('F', new LSystemRule(ruleF2, 1)));

    string ruleF3(">>&FGA");
    rules->insert(pair<char, LSystemRule*>('F', new LSystemRule(ruleF3, 0.54)));

    string ruleA("A");
    rules->insert(pair<char, LSystemRule*>('A', new LSystemRule(ruleA, 1.0)));
    
    string ruleG("G");
    rules->insert(pair<char, LSystemRule*>('G', new LSystemRule(ruleG, 1.0)));
    
    (*variableActions)['F'] = new DrawSegmentAction(0.4);
    (*variableActions)['G'] = new DrawSegmentMaterialAction(shinyBlue, 0.1);
    (*variableActions)['A'] = new DrawSegmentMaterialAction(shinyBlue, 0.1);
    
    return new SGLSystem(shinyBlue, base, rules, variableActions, 25, 3);

}

SGMatrixTransform *SGCity::getBlock(double blockWidth)
{
    double totalWidth = 0;
    double houseWidth = 0;
    SGHouse *house;
    SGMatrixTransform *houseTransform;
    Matrix4 houseMatrix;
    houseMatrix.toTranslationMatrix(0,0,0);
    SGMatrixTransform *block = new SGMatrixTransform(houseMatrix);

    while (totalWidth <  blockWidth - 10)
    {
      houseWidth = rand() % 7;
      if (houseWidth < 3) // stop houses being 1 unit wide 
      {
        houseWidth += 3; 
      }
     
      house = new SGHouse(material, seed, houseWidth, textures); // create the house
      houseMatrix.toTranslationMatrix(-blockWidth/2 + totalWidth + houseWidth/2, 0, 0); // move back into position
      houseTransform = new SGMatrixTransform(houseMatrix);

      houseTransform->addChild(house);
      block->addChild(houseTransform);

      totalWidth += houseWidth;
    }
    
    // Create last house to fill in gap to edge of block
    house = new SGHouse(material, seed, blockWidth - totalWidth, textures); // create the house
    houseMatrix.toTranslationMatrix((-blockWidth/2 + totalWidth + (blockWidth-totalWidth)/2), 0, 0); // move back into position
    houseTransform = new SGMatrixTransform(houseMatrix);

    houseTransform->addChild(house);
    block->addChild(houseTransform);
    
    return block;
}
