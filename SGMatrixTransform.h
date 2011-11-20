/* 
 * File:   SGMatrixTransform.h
 * Author: tom
 *
 * Created on October 31, 2011, 5:54 PM
 */

#ifndef SGMATRIXTRANSFORM_H
#define	SGMATRIXTRANSFORM_H

#include "SGGroup.h"
#include "Matrix4.h"

class SGMatrixTransform : public SGGroup {
public:
    SGMatrixTransform();
    SGMatrixTransform(const Matrix4 &tMat);
    void draw(Matrix4 mat);
    void setTransformationMatrix(Matrix4 mat);
private:
    Matrix4 transform;
};

#endif	/* SGMATRIXTRANSFORM_H */

