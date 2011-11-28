/* 
 * File:   SGLSystem.h
 * Author: tom
 *
 * Created on November 27, 2011, 3:52 PM
 */

#ifndef SGLSYSTEM_H
#define	SGLSYSTEM_H

#include "SGGeode.h"
#include "SGTurtle.h"
#include "LSystemRule.h"
#include <string>
#include <map>

class SGLSystem : public SGGeode {
public:
    SGLSystem(const Material &material, const std::string &startString, 
            std::multimap<char, LSystemRule*> *newRules, double rotateAngle, 
            double newSegmentSize,
            int maxRecursionDepth);
    virtual ~SGLSystem();
    
    void draw(Matrix4 mat);
private:
    SGTurtle *turtle;
    std::string start;
    std::multimap<char, LSystemRule*> *rules;
    
    double angle;
    double segmentSize;
    int maxDepth;
    
    void generateLSystem(const std::string &lSystem, int depth);
    void processConstant(char c);
    void processVariable(char c);
    std::string getRule(char variable);
    bool isVariable(char c);
};

#endif	/* SGLSYSTEM_H */

