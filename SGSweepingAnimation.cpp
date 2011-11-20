/* 
 * File:   SGSweepingAnimation.cpp
 * Author: tom
 * 
 * Created on November 3, 2011, 1:07 PM
 */
#include "SGSweepingAnimation.h"
#include "BasicMath.h"

const double SGSweepingAnimation::ROTATION_INC = 1.0;

SGSweepingAnimation::SGSweepingAnimation(double sweepMin, double sweepMax,
        double startAngle, double startInc, const Vector3& sweepAxis) 
        : currentRotation(startAngle), 
          rotationInc(startInc),
          min(sweepMin), max(sweepMax), axis(sweepAxis) {
    if (currentRotation > sweepMax) currentRotation = sweepMax;
    if (currentRotation < sweepMin) currentRotation = sweepMin;
    rotationMat.toRotationMatrix(currentRotation, axis);
}

SGSweepingAnimation::SGSweepingAnimation(const SGSweepingAnimation& orig) {
}

SGSweepingAnimation::~SGSweepingAnimation() {
}

void SGSweepingAnimation::draw(Matrix4 mat) {
    mat.multiply(rotationMat);
    
    for (unsigned int i = 0; i < children->size(); i++) {
        children->at(i)->draw(mat);
    }
    
    updateRotation();
}

void SGSweepingAnimation::updateRotation() {
    currentRotation += rotationInc;
    
    // Reverse direction if sweep limit reached
    if (currentRotation >= max || currentRotation <= min) {
        rotationInc = -rotationInc;
    }
    
    rotationMat.toRotationMatrix(currentRotation, axis);
}

