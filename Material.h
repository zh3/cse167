/* 
 * File:   Material.h
 * Author: tom
 *
 * Created on October 31, 2011, 6:20 PM
 */

#ifndef MATERIAL_H
#define	MATERIAL_H
#include "Vector4.h"
#include <GL/gl.h>

class Material {
public:
    Material(const Vector4 &newAmbient, const Vector4 &newDiffuse, 
             const Vector4 &newSpecular, const double newShininess);
//    Material(const Material& orig);
    virtual ~Material();
    
    void apply();
private:
    GLfloat ambient[4];
    GLfloat diffuse[4]; 
    GLfloat specular[4];
    GLfloat shininess;
    
    void vector4ToDoubleArray(const Vector4 &vector, float *array);
};

#endif	/* MATERIAL_H */

