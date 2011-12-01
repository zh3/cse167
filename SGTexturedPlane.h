/* 
 * File:   SGTexturedPlane.h
 * Author: tom
 *
 * Created on November 29, 2011, 6:55 PM
 */

#ifndef SGTEXTUREDPLANE_H
#define	SGTEXTUREDPLANE_H

#include "SGGeode.h"
#include "Texture.h"

class SGTexturedPlane : public SGGeode {
public:
    SGTexturedPlane(const Material &material, Texture *newTexture, 
            double newXSize, double newYSize, int newResolution);
    virtual ~SGTexturedPlane();
    void draw(Matrix4 mat);
private:
    double xSize;
    double ySize;
    int resolution;
    Texture *texture;
    Vector3 **vertices;
    Vector3 **textureCoordinates;
    
    void generateVertices();
    int getNumVertices();
};

#endif	/* SGTEXTUREDPLANE_H */

