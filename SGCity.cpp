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
using namespace std;

SGCity::SGCity(Material& material, double newSeed, double newBlockWidth) : SGGeode(material) {
  seed = newSeed;
  blockWidth = newBlockWidth;
  
  textures[0] = new Texture("./textures/wall1.ppm");
  textures[1] = new Texture("./textures/wall2.ppm");
  textures[2] = new Texture("./textures/wall3.ppm");
  textures[3] = new Texture("./textures/wall4.ppm");
  textures[4] = new Texture("./textures/roof1.ppm");
  textures[5] = new Texture("./textures/roof2.ppm");
  textures[6] = new Texture("./textures/roof3.ppm");
  textures[7] = new Texture("./textures/roof4.ppm");
  textures[8] = new Texture("./textures/brick1.ppm");
  textures[9] = new Texture("./textures/brick2.ppm");
  textures[10] = new Texture("./textures/plaster.ppm");

  city = getCity();
}

SGCity::~SGCity() {
    delete city;
}

void SGCity::draw(Matrix4 mat) {
    city->draw(mat);
}

SGNode *SGCity::getCity() {
    Vector4 ambient(0.2, 0.2, 0.2, 1.0);
    Vector4 diffuse(0.6, 0.6, 0.6, 1.0);
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
    block = getBlock();
    blockTranslateMatrix.multiply(blockTransform);
    block->setTransformationMatrix(blockTranslateMatrix);
    city->addChild(block);

    // bottom block
    blockTransform.toRotationMatrixY(180);
    blockTranslateMatrix.toTranslationMatrix(0, 0, 50);
    block = getBlock();
    blockTranslateMatrix.multiply(blockTransform);
    block->setTransformationMatrix(blockTranslateMatrix);
    city->addChild(block);   

    // left block
    blockTransform.toRotationMatrixY(270);
    blockTranslateMatrix.toTranslationMatrix(50, 0, 0);
    block = getBlock();
    blockTranslateMatrix.multiply(blockTransform);
    block->setTransformationMatrix(blockTranslateMatrix);
    city->addChild(block);

    // top block
    blockTransform.toRotationMatrixY(0);
    blockTranslateMatrix.toTranslationMatrix(0, 0, -50);
    block = getBlock();
    blockTranslateMatrix.multiply(blockTransform);
    block->setTransformationMatrix(blockTranslateMatrix);
    city->addChild(block);

    Texture *t = new Texture("textures/grass.ppm");
    Matrix4 floorTransformMatrix;
    floorTransformMatrix.toRotationMatrixX(-90.0);
    SGMatrixTransform *floorTransform 
            = new SGMatrixTransform(floorTransformMatrix);
    SGNode *floor = new SGTexturedPlane(material, t, 100, 100, 50);
    floorTransform->addChild(floor);
    
    city->addChild(floorTransform);

    // skybox
    Texture *texture;
    SGTexturedPlane *plane;
    SGMatrixTransform *transform;
    Matrix4 matrix, matrix2;

    // floor
   /*j texture = new Texture("./textures/wall3.ppm");
    plane = new SGTexturedPlane(material, texture, 1, 1, 1);
    
    matrix.toRotationMatrixX(90);
    matrix2.toScalingMatrix(100,100,1);
    matrix.multiply(matrix2);
    transform = new SGMatrixTransform(matrix);
    transform->addChild(plane);
    city->addChild(transform);
*/
    
    // front
    texture = new Texture("./textures/skyboxFront.ppm");
    plane = new SGTexturedPlane(material, texture, 1, 1, 1);

    matrix.toTranslationMatrix(0, 50, -50);
    matrix2.toScalingMatrix(100,100,1);
    matrix.multiply(matrix2);
    matrix2.toRotationMatrixZ(180);
    matrix.multiply(matrix2);
    matrix2.toRotationMatrixY(-180);
    matrix.multiply(matrix2);

    transform = new SGMatrixTransform(matrix);
    transform->addChild(plane);
    city->addChild(transform);

    // back
    texture = new Texture("./textures/skyboxBack.ppm");
    plane = new SGTexturedPlane(material, texture, 1, 1, 1);

    matrix.toTranslationMatrix(0, 50, 50);
    matrix2.toScalingMatrix(100,100,1);
    matrix.multiply(matrix2);
    matrix2.toRotationMatrixZ(180);
    matrix.multiply(matrix2);
        transform = new SGMatrixTransform(matrix);
    transform->addChild(plane);
    city->addChild(transform);

    // left
    texture = new Texture("./textures/skyboxLeft.ppm");
    plane = new SGTexturedPlane(material, texture, 1, 1, 1);

    matrix.toTranslationMatrix(-50, 50, 0);
    matrix2.toRotationMatrixY(90);
    matrix.multiply(matrix2);
    matrix2.toScalingMatrix(100,100,1);
    matrix.multiply(matrix2);
    matrix2.toRotationMatrixX(180);
    matrix.multiply(matrix2);
    transform = new SGMatrixTransform(matrix);
    transform->addChild(plane);
    city->addChild(transform);

    // right
    texture = new Texture("./textures/skyboxRight.ppm");
    plane = new SGTexturedPlane(material, texture, 1, 1, 1);

    matrix.toTranslationMatrix(50, 50, 0);
    matrix2.toRotationMatrixY(90);
    matrix.multiply(matrix2);
    matrix2.toScalingMatrix(100,100,1);
    matrix.multiply(matrix2);
    matrix2.toRotationMatrixX(180);
    matrix.multiply(matrix2);
    matrix2.toRotationMatrixY(-180);
    matrix.multiply(matrix2);

    transform = new SGMatrixTransform(matrix);
    transform->addChild(plane);
    city->addChild(transform);

    // top  
    texture = new Texture("./textures/skyboxTop.ppm");
    plane = new SGTexturedPlane(material, texture, 1, 1, 1);

    matrix.toTranslationMatrix(0, 100, 0);

    matrix2.toRotationMatrixX(90);
    matrix.multiply(matrix2);

    matrix2.toScalingMatrix(100,100,1);
    matrix.multiply(matrix2);

    matrix2.toRotationMatrixX(180);
    matrix.multiply(matrix2);


    transform = new SGMatrixTransform(matrix);
    transform->addChild(plane);
    city->addChild(transform);



    city->addChild(block);


    return city;
}

SGMatrixTransform *SGCity::getBlock()
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
      houseWidth = rand() % 10;
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
    houseMatrix.toTranslationMatrix((-blockWidth/2 + totalWidth + houseWidth/2), 0, 0); // move back into position
    houseTransform = new SGMatrixTransform(houseMatrix);

    houseTransform->addChild(house);
    block->addChild(houseTransform);
    
    return block;
}
