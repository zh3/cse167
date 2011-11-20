/* 
 * File:   SGLight.h
 * Author: tom
 *
 * Created on November 3, 2011, 6:40 PM
 */

#ifndef SGLIGHT_H
#define	SGLIGHT_H

#include "SGNode.h"
#include "Vector4.h"
#include "Vector3.h"
#include <GL/glut.h>

class SGLight : public SGNode {
public:
    SGLight(int lightIndex,Vector4 ambientLight, Vector4 diffuseLight, 
            Vector4 specularLight, Vector3 spotDir, double spotCutoff);
    virtual ~SGLight();
    
    void draw(Matrix4 mat);
private:
    GLenum lightEnum;
    //Vector4 ambient;
    //Vector4 diffuse;
    //Vector4 specular;
    Vector3 spotDirection;
    
    GLenum getLightEnum(int n);
};

#endif	/* SGLIGHT_H */

