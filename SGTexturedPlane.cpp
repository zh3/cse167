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
          vertices(new Vector3*[getNumVertices()]),
          textureCoordinates(new Vector3*[getNumVertices()]){
    generateVertices();
}

SGTexturedPlane::~SGTexturedPlane() {
    for (int i = 0; i < getNumVertices(); i++) {
        delete vertices[i];
    }
    
    delete [] vertices;
    
    for (int i = 0; i < getNumVertices(); i++) {
        delete textureCoordinates[i];
    }
    
    delete [] textureCoordinates;
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
    
    for (int i = 0; i < getNumVertices(); i++) {
        glNormal(normal);
        
        glTexture(textureCoordinates[i]);
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
            textureCoordinates[vertexPtr] 
                = new Vector3(i * xInc, j * yInc, 0.0);
            vertices[vertexPtr++] 
                = new Vector3(i * xInc + xOffset, j * yInc + yOffset, 0.0);
            
            textureCoordinates[vertexPtr] 
                = new Vector3(i * xInc, (j + 1) * yInc, 0.0);
            vertices[vertexPtr++] 
                = new Vector3(i * xInc + xOffset, (j + 1) * yInc + yOffset, 0.0);
            
            textureCoordinates[vertexPtr] 
                = new Vector3((i + 1) * xInc, (j + 1) * yInc, 0.0);
            vertices[vertexPtr++] 
                = new Vector3((i + 1) * xInc + xOffset, (j + 1) * yInc + yOffset, 0.0);
            
            textureCoordinates[vertexPtr] 
                = new Vector3((i + 1) * xInc, j * yInc, 0.0);
            vertices[vertexPtr++] 
                = new Vector3((i + 1) * xInc + xOffset, j * yInc + yOffset, 0.0);
        }
    }
    
    Vector3 *textureCoordinate;
    for (int i = 0; i < getNumVertices(); i++) {
        textureCoordinate = textureCoordinates[i];
        
        textureCoordinate->x = (textureCoordinate->x / xSize) * resolution;
        textureCoordinate->y = (textureCoordinate->y / xSize) * resolution;
	//	cout << "Texture coordinate is: " << *textureCoordinates[i] << endl;
    }
}

int SGTexturedPlane::getNumVertices() {
    return resolution * 4 * resolution;
}
