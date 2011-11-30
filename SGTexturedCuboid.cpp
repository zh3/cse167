/* 
 * File:   SGTexturedCuboid.cpp
 * Author: tom
 * 
 * Created on November 1, 2011, 11:44 AM
 */

#include "SGTexturedCuboid.h"
#include "SGTexturedPlane.h"
#include "SGMatrixTransform.h"

const int SGTexturedCuboid::DEFAULT_RESOLUTION = 3;

SGTexturedCuboid::SGTexturedCuboid(const Material &material, double newXSize, double newYSize, 
                   double newZSize, Texture *newTexture)
        : SGGeode(material), xSize(newXSize), ySize(newYSize), zSize(newZSize),
          texture(newTexture) {
    Matrix4 transform;
    Matrix4 rotation;
    
    SGTexturedPlane *frontFace 
        = new SGTexturedPlane(material, texture, xSize, ySize, 
            DEFAULT_RESOLUTION);
    transform.toTranslationMatrix(0.0, 0.0, zSize / 2.0);
    SGMatrixTransform *frontTransform = new SGMatrixTransform(transform);
    frontTransform->addChild(frontFace);
    
    SGTexturedPlane *backFace
        = new SGTexturedPlane(material, texture, xSize, ySize, 
                              DEFAULT_RESOLUTION);
    transform.toTranslationMatrix(0.0, 0.0, -zSize / 2.0);
    rotation.toRotationMatrixX(180.0);
    transform.multiply(rotation);
    SGMatrixTransform *backTransform = new SGMatrixTransform(transform);
    backTransform->addChild(backFace);
    
    SGTexturedPlane *leftFace
        = new SGTexturedPlane(material, texture, zSize, ySize, 
                              DEFAULT_RESOLUTION);
    transform.toTranslationMatrix(-xSize / 2.0, 0.0, 0.0);
    rotation.toRotationMatrixY(-90.0);
    transform.multiply(rotation);
    SGMatrixTransform *leftTransform = new SGMatrixTransform(transform);
    leftTransform->addChild(leftFace);
    
    SGTexturedPlane *rightFace
        = new SGTexturedPlane(material, texture, zSize, ySize, 
                              DEFAULT_RESOLUTION);
    transform.toTranslationMatrix(xSize / 2.0, 0.0, 0.0);
    rotation.toRotationMatrixY(90.0);
    transform.multiply(rotation);
    SGMatrixTransform *rightTransform = new SGMatrixTransform(transform);
    rightTransform->addChild(rightFace);
    
    SGTexturedPlane *topFace
        = new SGTexturedPlane(material, texture, xSize, zSize, 
                              DEFAULT_RESOLUTION);
    transform.toTranslationMatrix(0.0, ySize / 2.0, 0.0);
    rotation.toRotationMatrixX(-90.0);
    transform.multiply(rotation);
    SGMatrixTransform *topTransform = new SGMatrixTransform(transform);
    topTransform->addChild(topFace);
    
    SGTexturedPlane *bottomFace
        = new SGTexturedPlane(material, texture, xSize, zSize, 
                              DEFAULT_RESOLUTION);
    transform.toTranslationMatrix(0.0, -ySize / 2.0, 0.0);
    rotation.toRotationMatrixX(90.0);
    transform.multiply(rotation);
    SGMatrixTransform *bottomTransform = new SGMatrixTransform(transform);
    bottomTransform->addChild(bottomFace);
    
    faces[0] = frontTransform;
    faces[1] = backTransform;
    faces[2] = leftTransform;
    faces[3] = rightTransform;
    faces[4] = topTransform;
    faces[5] = bottomTransform;
}

SGTexturedCuboid::~SGTexturedCuboid() {
}

void SGTexturedCuboid::draw(Matrix4 mat) {
    for (int i = 0; i < 6; i++) {
        faces[i]->draw(mat);
    }
}

