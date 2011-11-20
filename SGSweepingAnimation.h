/* 
 * File:   SGSweepingAnimation.h
 * Author: tom
 *
 * Created on November 3, 2011, 1:07 PM
 */

#ifndef SGSWEEPINGANIMATION_H
#define	SGSWEEPINGANIMATION_H

#include "SGGroup.h"

class SGSweepingAnimation : public SGGroup {
public:
    SGSweepingAnimation(double sweepMin, double sweepMax, 
            double startAngle, double startInc, const Vector3& sweepAxis);
    SGSweepingAnimation(const SGSweepingAnimation& orig);
    virtual ~SGSweepingAnimation();
    void draw(Matrix4 mat);
private:
    static const double ROTATION_INC;
    double currentRotation;
    double rotationInc;
    double min;
    double max;
    Vector3 axis;
    Matrix4 rotationMat;
    
    void updateRotation();
};

#endif	/* SGSWEEPINGANIMATION_H */

