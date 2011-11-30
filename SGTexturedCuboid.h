/* 
 * File:   SGTexturedCuboid.h
 * Author: tom
 *
 * Created on November 1, 2011, 11:44 AM
 */

#ifndef SGTexturedCuboid_H
#define	SGTexturedCuboid_H

#include "SGGeode.h"
#include "Texture.h"
#include "SGTexturedPlane.h"

class SGTexturedCuboid : public SGGeode {
public:
    SGTexturedCuboid(const Material &material, double newXSize, 
             double newYSize, 
             double newZSize, Texture *newTexture = NULL);
    virtual ~SGTexturedCuboid();
    
    void draw(Matrix4 mat);
private:
    double xSize;
    double ySize;
    double zSize;
    static const int DEFAULT_RESOLUTION;
    
    Texture *texture;
    SGNode *faces[6];
};

#endif	/* SGTexturedCuboid_H */

