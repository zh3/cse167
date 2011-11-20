/* 
 * File:   SGLight.cpp
 * Author: tom
 * 
 * Created on November 3, 2011, 6:40 PM
 */

#include "SGLight.h"


SGLight::SGLight(int lightIndex, Vector4 ambient, Vector4 diffuse, 
        Vector4 specular, Vector3 spotDir, double spotCutoff) 
        : SGNode(), lightEnum(getLightEnum(lightIndex)), spotDirection(spotDir) {
    GLfloat defaultPosition[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat ambientLight[] = {ambient.x, ambient.y, ambient.z, ambient.o};
    GLfloat diffuseLight[] = {diffuse.x, diffuse.y, diffuse.z, diffuse.o};
    GLfloat specularLight[] = {specular.x, specular.y, specular.z, specular.o};
    GLfloat spotDirection[] = {spotDir.x, spotDir.y, spotDir.z};
    
    glEnable(lightEnum);
    glLightfv(lightEnum, GL_POSITION, defaultPosition);
    glLightfv(lightEnum, GL_AMBIENT, ambientLight);
    glLightfv(lightEnum, GL_DIFFUSE, diffuseLight);
    glLightfv(lightEnum, GL_SPECULAR, specularLight);
    glLightfv(lightEnum, GL_SPOT_DIRECTION, spotDirection);
    glLightf(lightEnum, GL_SPOT_CUTOFF, spotCutoff);
}

SGLight::~SGLight() {
    glDisable(lightEnum);
}

void SGLight::draw(Matrix4 mat) {
    Vector3 zero(0.0, 0.0, 0.0);
    
    
    glPushMatrix();
        glMultMatrixd(mat.getPointer());
        //Vector3 newPosition = mat.multiply(zero);
        //GLfloat position[] = {newPosition.x, newPosition.y, newPosition.z, 1.0};
        GLfloat position[] = {0.0, 0.0, 0.0, 1.0};
        GLfloat spotDir[] = {spotDirection.x, spotDirection.y, spotDirection.z};
        glLightfv(lightEnum, GL_POSITION, position);
        glLightfv(lightEnum, GL_SPOT_DIRECTION, spotDir);
    glPopMatrix();
    
}

GLenum SGLight::getLightEnum(int n) {
    switch (n) {
        case 1:
            return GL_LIGHT1;
        case 2:
            return GL_LIGHT2;
        case 3:
            return GL_LIGHT3;
        case 4:
            return GL_LIGHT4;
        case 5:
            return GL_LIGHT5;
        case 6:
            return GL_LIGHT6;
        case 7:
            return GL_LIGHT7;
        default:
            throw (n);
    }
}

