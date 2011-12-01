/* 
 * File:   SGTexturedPlane.cpp
 * Author: tom
 * 
 * Created on November 29, 2011, 6:55 PM
 */

#include "SGTexturedPlane.h"

SGTexturedPlane::SGTexturedPlane(const Material &material, Texture *newTexture, 
        double newXSize, double newYSize, int newResolution) 
        : SGGeode(material), 
          xSize(newXSize), ySize(newYSize),
          resolution(newResolution),
          texture(newTexture), 
          vertices(new Vector3*[getNumVertices()]) {
    generateVertices();
}

SGTexturedPlane::~SGTexturedPlane() {
    for (int i = 0; i < getNumVertices(); i++) {
        delete vertices[i];
    }
    
    delete [] vertices;
}

#include <iostream>
using namespace std;

void SGTexturedPlane::draw(Matrix4 mat) {
    Vector3 normal(0.0, 0.0, 1.0);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMultMatrixd(mat.getPointer());

    if (texture) texture->bindTexture();
    material.apply();
    glBegin(GL_QUADS);
    
    Vector3 textureCoordinates;
    for (int i = 0; i < getNumVertices(); i++) {
        glNormal(normal);
        
        textureCoordinates = *vertices[i];
        textureCoordinates.x = (textureCoordinates.x / xSize) * resolution;
        textureCoordinates.y = (textureCoordinates.y / ySize) * resolution;
        
        glTexture(textureCoordinates);
        glVertex(vertices[i]);
    }
    glEnd();
    
    glPopMatrix();
    
}

void SGTexturedPlane::generateVertices() {
    double xInc = xSize / resolution;
    double yInc = ySize / resolution;
    double xOffset = -xSize / 2.0;
    double yOffset = -ySize / 2.0;
    
    int vertexPtr = 0;
    for (int i = 0; i < resolution; i++) {
        for (int j = 0; j < resolution; j++) {
            vertices[vertexPtr++] 
                = new Vector3(i * xInc + xOffset, j * yInc + yOffset, 0.0);
            vertices[vertexPtr++] 
                = new Vector3(i * xInc + xOffset, (j + 1) * yInc + yOffset, 0.0);
            vertices[vertexPtr++] 
                = new Vector3((i + 1) * xInc + xOffset, (j + 1) * yInc + yOffset, 0.0);
            vertices[vertexPtr++] 
                = new Vector3((i + 1) * xInc + xOffset, j * yInc + yOffset, 0.0);
        }
    }
}

int SGTexturedPlane::getNumVertices() {
    return resolution * 4 * resolution;
}
