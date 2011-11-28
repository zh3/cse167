/* 
 * File:   SGLSystem.cpp
 * Author: tom
 * 
 * Created on November 27, 2011, 3:52 PM
 */

#include "SGLSystem.h"
#include <ctype.h>

using namespace std;

SGLSystem::SGLSystem(const Material &material, const string &startString, 
            const string &ruleString, double rotateAngle, double newSegmentSize,
            int maxRecursionDepth) 
        : SGGeode(material), 
          turtle(new SGTurtle(material)),
          start(startString), rule(ruleString), 
          angle(rotateAngle), segmentSize(newSegmentSize),
          maxDepth(maxRecursionDepth) {
    generateLSystem(start, 0);
}

SGLSystem::~SGLSystem() {
    delete turtle;
}

void SGLSystem::draw(Matrix4 mat) {
    turtle->draw(mat);
}

void SGLSystem::generateLSystem(const string &lsystem, int depth) {
//    turtle->drawMove(1.0);
//    
//    turtle->rotateH(90.0);
//    turtle->drawMove(1.0);
//    turtle->rotateL(90.0);
//    turtle->drawMove(1.0);
//    turtle->rotateU(90.0);
//    turtle->drawMove(1.0);
    
    for (unsigned int i = 0; i < lsystem.size(); i++) {
        char ch = lsystem[i];
        if (isVariable(ch)) {
            if (depth < maxDepth) {
                generateLSystem(getRule(ch), depth + 1);
            } else {
                processVariable(ch);
            }
        } else {
            processConstant(ch);
        }
    }
}

void SGLSystem::processConstant(char c) {
    switch (c) {
        case '+':
            turtle->rotateU(angle);
            break;
        case '-':
            turtle->rotateU(-angle);
            break;
        case '&':
            turtle->rotateL(angle);
            break;
        case '^':
            turtle->rotateL(-angle);
            break;
        case '<':
            turtle->rotateH(angle);
            break;
        case '>':
            turtle->rotateH(-angle);
            break;
        case '\\':
            turtle->rotateH(angle);
            break;
        case '/':
            turtle->rotateH(-angle);
            break;
        case '|':
            turtle->rotateU(180.0);
            break;
        case '[':
            turtle->pushState();
            break;
        case ']':
            turtle->popState();
            break;
        default:
            break;
    }
}

void SGLSystem::processVariable(char c) {
    turtle->drawMove(segmentSize);
}

string SGLSystem::getRule(char variable) {
    return rule;
}

bool SGLSystem::isVariable(char c) {
    return isupper(c);
}