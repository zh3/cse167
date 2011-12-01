/* 
 * File:   SGGrid.h
 * Author: tom
 *
 * Created on November 30, 2011, 9:07 PM
 */

#ifndef SGGRID_H
#define	SGGRID_H

#include "SGGroup.h"

class SGGrid : public SGGroup {
public:
    SGGrid(int rows, int cols, double _xSize, double _zSize);
    virtual ~SGGrid();
    void addChild(SGNode *child, int row, int col);
private:
    int nRows;
    int nCols;
    
    double xSize;
    double zSize;
    double xInc;
    double zInc;
};

#endif	/* SGGRID_H */

