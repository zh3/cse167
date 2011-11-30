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
using namespace std;

SGCity::SGCity(Material& material, double newSeed, double newBlockWidth) : SGGeode(material) {
  seed = newSeed;
  blockWidth = newBlockWidth;
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
    Matrix4 cityTransform, blockTransform, blockTranslateMatrix;;
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

    // testing the 100x100 floor
    /*blockTransform.toScalingMatrix(100, 1, 100);
    SGCuboid *floor = new SGCuboid(material, 1, .00001, 1);
    block = new SGMatrixTransform(blockTransform);
    block->addChild(floor);
    city->addChild(block);*/

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
     
      house = new SGHouse(material, seed, houseWidth); // create the house
      houseMatrix.toTranslationMatrix(-blockWidth/2 + totalWidth + houseWidth/2, 0, 0); // move back into position
      houseTransform = new SGMatrixTransform(houseMatrix);

      houseTransform->addChild(house);
      block->addChild(houseTransform);

      totalWidth += houseWidth;
    }
    
    // Create last house to fill in gap to edge of block
    house = new SGHouse(material, seed, blockWidth - totalWidth); // create the house
    houseMatrix.toTranslationMatrix((-blockWidth/2 + totalWidth + houseWidth/2), 0, 0); // move back into position
    houseTransform = new SGMatrixTransform(houseMatrix);

    houseTransform->addChild(house);
    block->addChild(houseTransform);
    
    return block;
}
