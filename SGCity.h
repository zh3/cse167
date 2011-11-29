/* 
 * File:   SGCity.h
 * Author: Cathy
 *
 * Created on November 20, 2011
 */

#ifndef SGCity_H
#define	SGCity_H

#include "SGGeode.h"
#include "SGMatrixTransform.h"

class SGCity : public SGGeode {
public:
    SGCity(Material& material, double newSeed, double newBlockWidth);
    virtual ~SGCity();
    void draw(Matrix4 mat);

private:
    double width;
    double seed;
    double blockWidth;

    SGNode *city;
    
    SGNode *getCity();
    SGMatrixTransform *getBlock();

};

#endif	/* SGCity_H*/

