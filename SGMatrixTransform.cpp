/* 
 * File:   SGMatrixTransform.cpp
 * Author: tom
 * 
 * Created on October 31, 2011, 5:54 PM
 */

#include "SGMatrixTransform.h"

SGMatrixTransform::SGMatrixTransform() : SGGroup() {
    transform.toIdentity();
}

SGMatrixTransform::SGMatrixTransform(const Matrix4 &tMat) 
        : SGGroup(), 
          transform(tMat) {
}

void SGMatrixTransform::draw(Matrix4 mat) {
    mat.multiply(transform);
    
    for (unsigned int i = 0; i < children->size(); i++) {
        children->at(i)->draw(mat);
    }
}

void SGMatrixTransform::setTransformationMatrix(Matrix4 mat) {
    transform = mat;
}
