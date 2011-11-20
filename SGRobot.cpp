/* 
 * File:   SGRobot.cpp
 * Author: tom
 * 
 * Created on November 2, 2011, 1:45 PM
 */

#include "SGRobot.h"
#include "SGMatrixTransform.h"
#include "SGSphere.h"
#include "SGCuboid.h"
#include "SGCylinder.h"
#include "Material.h"
#include <algorithm>
using namespace std;

const double SGRobot::BODY_X_SIZE = 0.7;
const double SGRobot::BODY_Y_SIZE = 1.0;
const double SGRobot::BODY_Z_SIZE = 0.7;
const double SGRobot::HEAD_RADIUS = 0.45;
const double SGRobot::ARM_SPACING = 0.02;
const double SGRobot::LEG_SPACING = 0.02;
const double SGRobot::UPPER_LEG_LENGTH = 0.4;
const double SGRobot::LOWER_LEG_LENGTH = 0.4;
const double SGRobot::UPPER_LEG_DIAMETER = 0.2;
const double SGRobot::LOWER_LEG_DIAMETER = 0.2;
const double SGRobot::UPPER_ARM_LENGTH = 0.4;
const double SGRobot::LOWER_ARM_LENGTH = 0.4;
const double SGRobot::UPPER_ARM_DIAMETER = 0.2;
const double SGRobot::LOWER_ARM_DIAMETER = 0.2;

const double SGRobot::DEFAULT_WIDTH = 2.0 * UPPER_ARM_DIAMETER + BODY_Z_SIZE;
const double SGRobot::DEFAULT_HEIGHT = BODY_Y_SIZE + 2.0 * HEAD_RADIUS
        + UPPER_LEG_LENGTH + LEG_SPACING + LOWER_LEG_LENGTH;
const double SGRobot::DEFAULT_DEPTH = max(BODY_Z_SIZE, HEAD_RADIUS * 2.0);

SGRobot::SGRobot(Material& limbMaterial, Material &_bodyMaterial, 
                 Material &_headMaterial, double newWidth, 
                 double newHeight, double newDepth)
        : SGGeode(limbMaterial), width(newWidth), height(newHeight), 
          depth(newDepth), bodyMaterial(_bodyMaterial), 
          headMaterial(_headMaterial), robot(getRobot()) {
}

SGRobot::SGRobot(Material& limbMaterial, Material &_bodyMaterial, 
          Material& _headMaterial, double newHeight)
        : SGGeode(limbMaterial), width(DEFAULT_WIDTH * (newHeight / DEFAULT_HEIGHT)),
          height(newHeight), 
          depth(DEFAULT_DEPTH * (newHeight / DEFAULT_HEIGHT)), 
          bodyMaterial(_bodyMaterial), 
          headMaterial(_headMaterial), robot(getRobot())  {
}

SGRobot::~SGRobot() {
    delete robot;
}

void SGRobot::draw(Matrix4 mat) {
    robot->draw(mat);
}

SGNode *SGRobot::getRobot() {
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
    SGNode *robotLeftLeg = getRobotLimb(material, UPPER_LEG_LENGTH, 
            UPPER_LEG_DIAMETER, LOWER_LEG_LENGTH, LOWER_LEG_DIAMETER, 
            LEG_SPACING);
    robotTransform.toTranslationMatrix(
                -(BODY_X_SIZE / 2.0) + (UPPER_LEG_DIAMETER / 2.0), 
                -BODY_Y_SIZE / 2.0, 0.0);
    SGMatrixTransform *leftLegTransform = new SGMatrixTransform(robotTransform);
    leftLegTransform->addChild(robotLeftLeg);
    
    // Right Leg
    SGNode *robotRightLeg = getRobotLimb(material, UPPER_LEG_LENGTH, 
            UPPER_LEG_DIAMETER, LOWER_LEG_LENGTH, LOWER_LEG_DIAMETER, 
            LEG_SPACING);
    robotTransform.toTranslationMatrix(
                (BODY_X_SIZE / 2.0) - (UPPER_LEG_DIAMETER / 2.0), 
                -BODY_Y_SIZE / 2.0, 0.0);
    SGMatrixTransform *rightLegTransform 
            = new SGMatrixTransform(robotTransform);
    rightLegTransform->addChild(robotRightLeg);
    
    // Left Arm
    SGNode *robotLeftArm = getRobotLimb(material, UPPER_ARM_LENGTH, 
            UPPER_ARM_DIAMETER, LOWER_ARM_LENGTH, LOWER_ARM_DIAMETER, 
            ARM_SPACING);
    robotTransform.toTranslationMatrix(
                -(BODY_X_SIZE / 2.0) - (UPPER_LEG_DIAMETER / 2.0), 
                BODY_Y_SIZE / 2.0, 0.0);
    SGMatrixTransform *leftArmTransform = new SGMatrixTransform(robotTransform);
    leftArmTransform->addChild(robotLeftArm);
    
    // Right Arm
    SGNode *robotRightArm = getRobotLimb(material, UPPER_ARM_LENGTH, 
            UPPER_ARM_DIAMETER, LOWER_ARM_LENGTH, LOWER_ARM_DIAMETER, 
            ARM_SPACING);
    robotTransform.toTranslationMatrix(
                (BODY_X_SIZE / 2.0) + (UPPER_LEG_DIAMETER / 2.0), 
                BODY_Y_SIZE / 2.0, 0.0);
    SGMatrixTransform *rightArmTransform 
            = new SGMatrixTransform(robotTransform);
    rightArmTransform->addChild(robotRightArm);
    
    robot->addChild(robotCore);
    robot->addChild(leftLegTransform);
    robot->addChild(rightLegTransform);
    robot->addChild(leftArmTransform);
    robot->addChild(rightArmTransform);
    return robot;
}

SGNode *SGRobot::getRobotLimb(const Material &limbMaterial, 
        double upperLimbLength, double upperLimbWidth, 
        double lowerLimbLength, double lowerLimbWidth,
        double limbSpacing) {
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
    
    // Bind limb together and map the top of the limb to the origin
    limbTranslation.toTranslationMatrix(0.0, 
            -(upperLimbLength + spacingOffset), 0.0);
    SGMatrixTransform *overallLimbTransform
            = new SGMatrixTransform(limbTranslation);
    
    overallLimbTransform->addChild(upperLimbTransform);
    overallLimbTransform->addChild(lowerLimbTransform);

    return overallLimbTransform;
}

SGNode *SGRobot::getRobotCore(const Material &headMaterial, 
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
