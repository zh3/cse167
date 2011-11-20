/* 
 * File:   SGRobot.cpp
 * Author: tom
 * 
 * Created on November 2, 2011, 1:45 PM
 */

#include "SGAnimatedRobot.h"
#include "SGMatrixTransform.h"
#include "SGSphere.h"
#include "SGCuboid.h"
#include "SGCylinder.h"
#include "Material.h"
#include "SGLight.h"
#include <algorithm>
using namespace std;

const double SGAnimatedRobot::BODY_X_SIZE = 0.7;
const double SGAnimatedRobot::BODY_Y_SIZE = 1.0;
const double SGAnimatedRobot::BODY_Z_SIZE = 0.7;
const double SGAnimatedRobot::HEAD_RADIUS = 0.45;
const double SGAnimatedRobot::ARM_SPACING = 0.02;
const double SGAnimatedRobot::LEG_SPACING = 0.02;
const double SGAnimatedRobot::UPPER_LEG_LENGTH = 0.4;
const double SGAnimatedRobot::LOWER_LEG_LENGTH = 0.4;
const double SGAnimatedRobot::UPPER_LEG_DIAMETER = 0.2;
const double SGAnimatedRobot::LOWER_LEG_DIAMETER = 0.2;
const double SGAnimatedRobot::UPPER_ARM_LENGTH = 0.4;
const double SGAnimatedRobot::LOWER_ARM_LENGTH = 0.4;
const double SGAnimatedRobot::UPPER_ARM_DIAMETER = 0.2;
const double SGAnimatedRobot::LOWER_ARM_DIAMETER = 0.2;

const double SGAnimatedRobot::DEFAULT_WIDTH = 2.0 * UPPER_ARM_DIAMETER + BODY_Z_SIZE;
const double SGAnimatedRobot::DEFAULT_HEIGHT = BODY_Y_SIZE + 2.0 * HEAD_RADIUS
        + UPPER_LEG_LENGTH + LEG_SPACING + LOWER_LEG_LENGTH;
const double SGAnimatedRobot::DEFAULT_DEPTH = max(BODY_Z_SIZE, HEAD_RADIUS * 2.0);

SGAnimatedRobot::SGAnimatedRobot(Material& limbMaterial, Material &_bodyMaterial, 
                 Material &_headMaterial, double newWidth, 
                 double newHeight, double newDepth)
        : SGGeode(limbMaterial), width(newWidth), height(newHeight), 
          depth(newDepth), bodyMaterial(_bodyMaterial), 
          headMaterial(_headMaterial), robot(getRobot()) {
}

SGAnimatedRobot::SGAnimatedRobot(Material& limbMaterial, Material &_bodyMaterial, 
          Material& _headMaterial, double newHeight)
        : SGGeode(limbMaterial), width(DEFAULT_WIDTH * (newHeight / DEFAULT_HEIGHT)),
          height(newHeight), 
          depth(DEFAULT_DEPTH * (newHeight / DEFAULT_HEIGHT)), 
          bodyMaterial(_bodyMaterial), 
          headMaterial(_headMaterial), robot(getRobot())  {
}

SGAnimatedRobot::~SGAnimatedRobot() {
    delete robot;
}

void SGAnimatedRobot::draw(Matrix4 mat) {
    robot->draw(mat);
}

SGNode *SGAnimatedRobot::getRobot() {
    double headTopYOffset = BODY_Y_SIZE / 2.0 + HEAD_RADIUS * 2.0;
    double halfHeightYOffset = DEFAULT_HEIGHT / 2.0;
    
    Matrix4 yTranslation;
    yTranslation.toTranslationMatrix(0.0, -headTopYOffset + halfHeightYOffset,
                                     0.0);
    
    Matrix4 robotTransform;
    robotTransform.toScalingMatrix(width / DEFAULT_WIDTH, 
            height / DEFAULT_HEIGHT, depth / DEFAULT_DEPTH);
    robotTransform.multiply(yTranslation);

    SGMatrixTransform *robot = new SGMatrixTransform(robotTransform);
    
    // Head and Torso
    SGNode *robotCore = getRobotCore(headMaterial, bodyMaterial, BODY_X_SIZE, 
            BODY_Y_SIZE, BODY_Z_SIZE, HEAD_RADIUS);
    
    
    
    // Left Leg
    
    // Animation
    Vector3 rotationAxis(1.0, 0.0, 0.0);
    
    SGSweepingAnimation *leftLowerLegAnimation 
        = new SGSweepingAnimation(0.0, 45.0, 0.0, 1.0, rotationAxis);
    SGNode *robotLeftLeg = getRobotLimb(material, UPPER_LEG_LENGTH, 
            UPPER_LEG_DIAMETER, LOWER_LEG_LENGTH, LOWER_LEG_DIAMETER, 
            LEG_SPACING, leftLowerLegAnimation);
    robotTransform.toTranslationMatrix(
                -(BODY_X_SIZE / 2.0) + (UPPER_LEG_DIAMETER / 2.0), 
                -BODY_Y_SIZE / 2.0, 0.0);

    SGSweepingAnimation *leftLegAnimation 
            = new SGSweepingAnimation(-45.0, 0.0, 0.0, -1, rotationAxis);
    leftLegAnimation->addChild(robotLeftLeg);
    SGMatrixTransform *leftLegTransform = new SGMatrixTransform(robotTransform);
    leftLegTransform->addChild(leftLegAnimation);
    
    // Right Leg
    SGSweepingAnimation *rightLowerLegAnimation 
        = new SGSweepingAnimation(0.0, 45.0, 45.0, -1, rotationAxis);
    
    SGNode *robotRightLeg = getRobotLimb(material, UPPER_LEG_LENGTH, 
            UPPER_LEG_DIAMETER, LOWER_LEG_LENGTH, LOWER_LEG_DIAMETER, 
            LEG_SPACING, rightLowerLegAnimation);
    robotTransform.toTranslationMatrix(
                (BODY_X_SIZE / 2.0) - (UPPER_LEG_DIAMETER / 2.0), 
                -BODY_Y_SIZE / 2.0, 0.0);
    SGSweepingAnimation *rightLegAnimation 
            = new SGSweepingAnimation(-45.0, 0.0, -45.0, 1, rotationAxis);
    rightLegAnimation->addChild(robotRightLeg);
    SGMatrixTransform *rightLegTransform 
            = new SGMatrixTransform(robotTransform);
    rightLegTransform->addChild(rightLegAnimation);
    
    // Left Arm
    SGSweepingAnimation *leftLowerArmAnimation 
        = new SGSweepingAnimation(-45.0, 0.0, -45.0, 1, rotationAxis);
    
    SGNode *robotLeftArm = getRobotLimb(material, UPPER_ARM_LENGTH, 
            UPPER_ARM_DIAMETER, LOWER_ARM_LENGTH, LOWER_ARM_DIAMETER, 
            ARM_SPACING, leftLowerArmAnimation);
    robotTransform.toTranslationMatrix(
                -(BODY_X_SIZE / 2.0) - (UPPER_LEG_DIAMETER / 2.0), 
                BODY_Y_SIZE / 2.0, 0.0);
    SGSweepingAnimation *leftArmAnimation 
            = new SGSweepingAnimation(-25.0, 25.0, 25.0, -1, rotationAxis);
    leftArmAnimation->addChild(robotLeftArm);
    SGMatrixTransform *leftArmTransform = new SGMatrixTransform(robotTransform);
    leftArmTransform->addChild(leftArmAnimation);
    
    // Right Arm
    SGSweepingAnimation *rightLowerArmAnimation 
        = new SGSweepingAnimation(-45.0, 0.0, 0, -1, rotationAxis);
    
    SGNode *robotRightArm = getFlashlightLimb(material, UPPER_ARM_LENGTH, 
            UPPER_ARM_DIAMETER, LOWER_ARM_LENGTH, LOWER_ARM_DIAMETER, 
            ARM_SPACING, rightLowerArmAnimation);
    robotTransform.toTranslationMatrix(
                (BODY_X_SIZE / 2.0) + (UPPER_LEG_DIAMETER / 2.0), 
                BODY_Y_SIZE / 2.0, 0.0);
    SGSweepingAnimation *rightArmAnimation 
            = new SGSweepingAnimation(-25.0, 25.0, -25.0, 1, rotationAxis);
    rightArmAnimation->addChild(robotRightArm);
    SGMatrixTransform *rightArmTransform 
            = new SGMatrixTransform(robotTransform);
    rightArmTransform->addChild(rightArmAnimation);
    
    robot->addChild(robotCore);
    robot->addChild(leftLegTransform);
    robot->addChild(rightLegTransform);
    robot->addChild(leftArmTransform);
    robot->addChild(rightArmTransform);
    //robot->addChild(getLight());
    
    return robot;
}

SGNode *SGAnimatedRobot::getFlashlightLimb(const Material& limbMaterial, 
        double upperLimbLength, 
        double upperLimbWidth, 
        double lowerLimbLength, 
        double lowerLimbWidth, 
        double limbSpacing, 
        SGSweepingAnimation* lowerLimbAnimation) {
    /*
    Matrix4 mat;
    mat.toIdentity();
    
    SGMatrixTransform *limbTransform = new SGMatrixTransform(mat);
    SGNode *limb = getRobotLimb(limbMaterial, upperLimbLength, upperLimbWidth, 
            lowerLimbLength, lowerLimbWidth, limbSpacing, lowerLimbAnimation);
    limbTransform->addChild(limb);
    
    mat.toTranslationMatrix(0.0, -(UPPER_ARM_LENGTH + LOWER_ARM_LENGTH + ARM_SPACING), 0.0);
    SGMatrixTransform *lightTransform = new SGMatrixTransform(mat);
    lightTransform->addChild(getLight());
    limbTransform->addChild(lightTransform);
    
    return limbTransform;
    */
    
    Matrix4 limbTranslation;
    double lowerLimbRadius = lowerLimbWidth / 2.0;
    double upperLimbRadius = upperLimbWidth / 2.0;
    double spacingOffset = limbSpacing / 2.0;
    
    // Create Upper Limb
    limbTranslation.toTranslationMatrix(0.0, 
            upperLimbLength / 2.0 + spacingOffset, 0.0);
    SGMatrixTransform *upperLimbTransform
            = new SGMatrixTransform(limbTranslation);
    SGCylinder *upperLimb = new SGCylinder(limbMaterial, upperLimbRadius, 
            upperLimbLength);
    upperLimbTransform->addChild(upperLimb);
    
    // Create Lower Limb
    limbTranslation.toTranslationMatrix(0.0, 
            -(lowerLimbLength / 2.0 + spacingOffset), 0.0);
    SGMatrixTransform *lowerLimbTransform
            = new SGMatrixTransform(limbTranslation);
    SGCylinder *lowerLimb = new SGCylinder(limbMaterial, lowerLimbRadius,
            lowerLimbLength);
    lowerLimbTransform->addChild(lowerLimb);
    lowerLimbTransform->addChild(getFlashlight());
    lowerLimbAnimation->addChild(lowerLimbTransform);
    
    // Bind limb together and map the top of the limb to the origin
    limbTranslation.toTranslationMatrix(0.0, 
            -(upperLimbLength + spacingOffset), 0.0);
    SGMatrixTransform *overallLimbTransform
            = new SGMatrixTransform(limbTranslation);
    
    overallLimbTransform->addChild(upperLimbTransform);
    overallLimbTransform->addChild(lowerLimbAnimation);

    return overallLimbTransform;
}

SGNode *SGAnimatedRobot::getRobotLimb(const Material &limbMaterial, 
        double upperLimbLength, double upperLimbWidth, 
        double lowerLimbLength, double lowerLimbWidth,
        double limbSpacing, SGSweepingAnimation *lowerLimbAnimation) {
    Matrix4 limbTranslation;
    double lowerLimbRadius = lowerLimbWidth / 2.0;
    double upperLimbRadius = upperLimbWidth / 2.0;
    double spacingOffset = limbSpacing / 2.0;
    
    // Create Upper Limb
    limbTranslation.toTranslationMatrix(0.0, 
            upperLimbLength / 2.0 + spacingOffset, 0.0);
    SGMatrixTransform *upperLimbTransform
            = new SGMatrixTransform(limbTranslation);
    SGCylinder *upperLimb = new SGCylinder(limbMaterial, upperLimbRadius, 
            upperLimbLength);
    upperLimbTransform->addChild(upperLimb);
    
    // Create Lower Limb
    limbTranslation.toTranslationMatrix(0.0, 
            -(lowerLimbLength / 2.0 + spacingOffset), 0.0);
    SGMatrixTransform *lowerLimbTransform
            = new SGMatrixTransform(limbTranslation);
    SGCylinder *lowerLimb = new SGCylinder(limbMaterial, lowerLimbRadius,
            lowerLimbLength);
    lowerLimbTransform->addChild(lowerLimb);
    lowerLimbAnimation->addChild(lowerLimbTransform);
    
    // Bind limb together and map the top of the limb to the origin
    limbTranslation.toTranslationMatrix(0.0, 
            -(upperLimbLength + spacingOffset), 0.0);
    SGMatrixTransform *overallLimbTransform
            = new SGMatrixTransform(limbTranslation);
    
    overallLimbTransform->addChild(upperLimbTransform);
    overallLimbTransform->addChild(lowerLimbAnimation);

    return overallLimbTransform;
}

SGNode *SGAnimatedRobot::getRobotCore(const Material &headMaterial, 
        const Material &bodyMaterial, double bodyXSize, double bodyYSize, 
        double bodyZSize, double headRadius) {
    Matrix4 coreTransformation;
    
    coreTransformation.toIdentity();
    SGMatrixTransform *coreTransform
            = new SGMatrixTransform(coreTransformation);
    SGCuboid *torso 
            = new SGCuboid(bodyMaterial, bodyXSize, bodyYSize, bodyZSize);
    coreTransform->addChild(torso);
    
    coreTransformation.toTranslationMatrix(0.0, bodyYSize / 2.0 + headRadius, 
                                           0.0);
    
    SGMatrixTransform *headTransform
            = new SGMatrixTransform(coreTransformation);
    SGSphere *head = new SGSphere(headMaterial, headRadius);
    headTransform->addChild(head);
    coreTransform->addChild(headTransform);
    
    return coreTransform;
}

SGNode *SGAnimatedRobot::getFlashlight() {
    Vector4 ambient(0.2, 0.2, 0.2, 1.0);
    Vector4 diffuse(1.0, 1.0, 1.0, 1.0);
    Vector4 specular(1.0, 1.0, 1.0, 1.0);
    Vector3 direction(0.0, -1.0, 0.0);
    
    Matrix4 transform;
    transform.toTranslationMatrix(0.0, -0.1, 0.0);
    SGMatrixTransform *lightTransform = new SGMatrixTransform(transform);
    SGLight *l = new SGLight(1, ambient, diffuse, specular, direction, 40.0);
    lightTransform->addChild(l);
    
    return lightTransform;
}

