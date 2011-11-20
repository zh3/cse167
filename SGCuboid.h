/* 
 * File:   SGCuboid.h
 * Author: tom
 *
 * Created on November 1, 2011, 11:44 AM
 */

#ifndef SGCUBOID_H
#define	SGCUBOID_H

#include "SGGeode.h"

class SGCuboid : public SGGeode {
public:
    SGCuboid(const Material &material, double newXSize, double newYSize, 
             double newZSize);
    virtual ~SGCuboid();
    
    void draw(Matrix4 mat);
private:
    double xSize;
    double ySize;
    double zSize;
};

#endif	/* SGCUBOID_H */

