/* 
 * File:   SGRobot.h
 * Author: tom
 *
 * Created on November 2, 2011, 1:45 PM
 */

#ifndef SGANIMATEDROBOT_H
#define	SGANIMATEDROBOT_H

#include "SGGeode.h"
#include "SGSweepingAnimation.h"

class SGAnimatedRobot : public SGGeode {
public:
    SGAnimatedRobot(Material& limbMaterial, Material &bodyMaterial, 
            Material& headMaterial, double newWidth, 
            double newHeight, double newDepth /* = 0 */);
    SGAnimatedRobot(Material& limbMaterial, Material &bodyMaterial, 
            Material &headMaterial, double height);
    virtual ~SGAnimatedRobot();
    void draw(Matrix4 mat);
private:
    static const double BODY_X_SIZE;
    static const double BODY_Y_SIZE;
    static const double BODY_Z_SIZE;
    static const double HEAD_RADIUS;
    static const double ARM_SPACING;
    static const double LEG_SPACING;
    static const double UPPER_LEG_LENGTH;
    static const double LOWER_LEG_LENGTH;
    static const double UPPER_LEG_DIAMETER;
    static const double LOWER_LEG_DIAMETER;
    static const double UPPER_ARM_LENGTH;
    static const double LOWER_ARM_LENGTH;
    static const double UPPER_ARM_DIAMETER;
    static const double LOWER_ARM_DIAMETER;
    
    static const double DEFAULT_WIDTH;
    static const double DEFAULT_HEIGHT;
    static const double DEFAULT_DEPTH;
    
    double width;
    double height;
    double depth;
    Material bodyMaterial;
    Material headMaterial;
    SGNode *robot;
    
    SGNode *getRobot();
    SGNode *getRobotLimb(const Material &limbMaterial, 
        double upperLimbLength, double upperLimbWidth, 
        double lowerLimbLength, double lowerLimbWidth,
        double limbSpacing, SGSweepingAnimation *lowerLimbAnimation);
    SGNode *getFlashlightLimb(const Material &limbMaterial, 
        double upperLimbLength, double upperLimbWidth, 
        double lowerLimbLength, double lowerLimbWidth,
        double limbSpacing, SGSweepingAnimation *lowerLimbAnimation);
    SGNode *getRobotCore(const Material &headMaterial, 
        const Material &bodyMaterial, double bodyXSize, double bodyYSize, 
        double bodyZSize, double headRadius);
    SGNode *getFlashlight();
};

#endif	/* SGROBOT_H */

