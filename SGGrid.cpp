/* 
 * File:   SGGrid.cpp
 * Author: tom
 * 
 * Created on November 30, 2011, 9:07 PM
 */

#include "SGGrid.h"
#include "SGMatrixTransform.h"

#include <iostream>
using namespace std;
SGGrid::SGGrid(int rows, int cols, double _xSize, double _zSize)
        : nRows(rows), nCols(cols), xSize(_xSize), zSize(_zSize),
          xInc(xSize / nCols), zInc(zSize / nRows),
          occupied(new bool*[nRows]) {
    for (int i = 0; i < nRows; i++) {
        occupied[i] = new bool[nCols];
    }
    
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            occupied[i][j] = false;
        }
    }
}

SGGrid::~SGGrid() {
    for (int i = 0; i < nRows; i++) {
        delete [] occupied[i];
    }
    
    delete [] occupied;
}

void SGGrid::addChild(SGNode* child, int row, int col) {
    Matrix4 transform;
    
    double xOffset = xInc / 2.0 + col * xInc - xSize / 2.0;
    double zOffset = zInc / 2.0 + row * zInc - zSize / 2.0;
    
    cout << "x Offset is "<< xOffset << " z offset is: " << zOffset << endl;
    
    transform.toTranslationMatrix(xOffset, 0.0, zOffset);
    SGMatrixTransform *translation = new SGMatrixTransform(transform);
    translation->addChild(child);
    
    SGGroup::addChild(translation);
    //occupied[row][col] = true;
}

void SGGrid::draw(Matrix4 mat) {
    for (unsigned int i = 0; i < children->size(); i++) {
        children->at(i)->draw(mat);
    }
}

bool SGGrid::isOccupied(int row, int col) {
    return false;
}

