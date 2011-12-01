/* 
 * File:   SGGrid.cpp
 * Author: tom
 * 
 * Created on November 30, 2011, 9:07 PM
 */

#include "SGGrid.h"
#include "SGMatrixTransform.h"

SGGrid::SGGrid(int rows, int cols, double _xSize, double _zSize)
        : nRows(rows), nCols(cols), xSize(_xSize), zSize(_zSize),
          xInc(xSize / nRows), zInc(zSize / nCols) {
}

SGGrid::~SGGrid() {
}

void SGGrid::addChild(SGNode* child, int row, int col) {
    Matrix4 transform;
    
    double xOffset = xInc + row * xInc - xSize / 2.0;
    double zOffset = zInc + col * zInc - zSize / 2.0;
    
    transform.toTranslationMatrix(xOffset, 0.0, zOffset);
    SGMatrixTransform *translation = new SGMatrixTransform(transform);
    translation->addChild(child);
    
    SGGroup::addChild(translation);
}

void SGGrid::draw(Matrix4 mat) {
    for (unsigned int i = 0; i < children->size(); i++) {
        children->at(i)->draw(mat);
    }
}

