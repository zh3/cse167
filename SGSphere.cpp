/* 
 * File:   SGSphere.cpp
 * Author: tom
 * 
 * Created on November 1, 2011, 12:28 AM
 */

#include <GL/freeglut_std.h>

#include "SGSphere.h"
#include "Matrix4.h"

const GLint SGSphere::nSlices = 10;
const GLint SGSphere::nStacks = 10;

SGSphere::SGSphere(const Material &material, GLdouble newRadius) 
        :  SGGeode(material), radius(newRadius) {
}

SGSphere::~SGSphere() {
}

void SGSphere::draw(Matrix4 mat) {
    material.apply();
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    //glLoadMatrixd(mat.getPointer());
    glMultMatrixd(mat.getPointer());
    glutSolidSphere(radius, nSlices, nStacks);
    glPopMatrix();
}
