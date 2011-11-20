/* 
 * File:   SGGeode.cpp
 * Author: tom
 * 
 * Created on October 31, 2011, 6:15 PM
 */

#include "SGGeode.h"

SGGeode::SGGeode(const Material &geodeMaterial) : material(geodeMaterial) {
}

SGGeode::~SGGeode() {
}

void SGGeode::glVertex(const Vector3 &v) {
    glVertex3d(v.x, v.y, v.z);
}

void SGGeode::glVertex(const Vector3 *v) {
    glVertex3d(v->x, v->y, v->z);
}

void SGGeode::glNormal(const Vector3 &v) {
    glNormal3d(v.x, v.y, v.z);
}

void SGGeode::glNormal(const Vector3 *v) {
    glNormal3d(v->x, v->y, v->z);
}

void SGGeode::glTexture(const Vector3 &v) {
    glTexCoord2d(v.x, v.y);
}

void SGGeode::glTexture(const Vector3 *v) {
    glTexCoord2d(v->x, v->y);
}

void SGGeode::deleteVector3Array(Vector3 **array, int size) {
    for (int i = 0; i < size; i++) {
        delete array[i];
    }
    
    delete [] array;
}