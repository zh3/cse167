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
#include "Texture.h"

class SGHouse : public SGGeode {
public:
    SGHouse(Material& material, double newSeed);
    SGHouse(Material& material, double newSeed, double wid, Texture *tex[]);
    virtual ~SGHouse();
    void draw(Matrix4 mat);
   
private:
    double width;
    double seed;
    Texture **textures;

    SGNode *house;
    
    SGNode *getHouse(Texture *textures[]);
    void addRoof(SGMatrixTransform *house, double width, double stories, Texture *textures[],
      int innerRoofTex); 
    void addSidewaysRoof(SGMatrixTransform *house, double width, double stories);
    void addWindows(SGMatrixTransform *house, double width, double stories, Texture *textures[]); 
    void addChimney(SGMatrixTransform *house, double width, double stories, Texture *textures[]);
    void addBeams(SGMatrixTransform *house, double width, double stories, Texture *textures[]);

};

#endif	/* SGHOUSE_H*/

