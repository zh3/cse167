/* 
 * File:   Material.cpp
 * Author: tom
 * 
 * Created on October 31, 2011, 6:20 PM
 */

#include <GL/glut.h>
#include "Material.h"

Material::Material(const Vector4 &newAmbient, const Vector4 &newDiffuse, 
                   const Vector4 &newSpecular, const double newShininess) {
    vector4ToDoubleArray(newAmbient, ambient);
    vector4ToDoubleArray(newDiffuse, diffuse);
    vector4ToDoubleArray(newSpecular, specular);
    shininess = newShininess;
}

//Material::Material(const Material& orig) {
//}

Material::~Material() {
}

void Material::vector4ToDoubleArray(const Vector4& vector, float* array) {
    array[0] = vector.x;
    array[1] = vector.y;
    array[2] = vector.z;
    array[3] = vector.o;
}
#include <iostream>
using namespace std;
void Material::apply() {
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);
}

