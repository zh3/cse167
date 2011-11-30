/* 
 * File:   SGHouse.h
 * Author: Cathy
 *
 * Created on November 20, 2011
 */

#ifndef SGHOUSE_H
#define	SGHOUSE_H

#include "SGGeode.h"
#include "SGMatrixTransform.h"

class SGHouse : public SGGeode {
public:
    SGHouse(Material& material, double newSeed);
    SGHouse(Material& material, double newSeed, double wid);
    virtual ~SGHouse();
    void draw(Matrix4 mat);
   
private:
    double width;
    double seed;

    SGNode *house;
    
    SGNode *getHouse();
    void addRoof(SGMatrixTransform *house, double width, double stories); 
    void addSidewaysRoof(SGMatrixTransform *house, double width, double stories);
    void addWindows(SGMatrixTransform *house, double width, double stories); 
    void addChimney(SGMatrixTransform *house, double width, double stories);
    void addBeams(SGMatrixTransform *house, double width, double stories);

};

#endif	/* SGHOUSE_H*/

