/* 
 * File:   SGCuboid.cpp
 * Author: tom
 * 
 * Created on November 1, 2011, 11:44 AM
 */

#include "SGCuboid.h"

SGCuboid::SGCuboid(const Material &material, double newXSize, double newYSize, 
                   double newZSize)
        : SGGeode(material), xSize(newXSize), ySize(newYSize), zSize(newZSize) {
}

SGCuboid::~SGCuboid() {
}

void SGCuboid::draw(Matrix4 mat) {
    material.apply();
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    //glLoadMatrixd(mat.getPointer());
    glMultMatrixd(mat.getPointer());
    glScaled(xSize, ySize, zSize);
    glutSolidCube(1.0);
    glPopMatrix();
}

