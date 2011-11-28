/* 
 * File:   SGLSystem.cpp
 * Author: tom
 * 
 * Created on November 27, 2011, 3:52 PM
 */

#include "SGLSystem.h"
#include <ctype.h>
#include <iostream>

using namespace std;

SGLSystem::SGLSystem(const Material &material, const string &startString, 
            std::multimap<char, LSystemRule*> *newRules, double rotateAngle, 
            double newSegmentSize, int maxRecursionDepth) 
        : SGGeode(material), 
          turtle(new SGTurtle(material)),
          start(startString), rules(newRules),
          angle(rotateAngle), segmentSize(newSegmentSize),
          maxDepth(maxRecursionDepth) {
    generateLSystem(start, 0);
}

SGLSystem::~SGLSystem() {
    delete turtle;
    
    multimap<char, LSystemRule*>::iterator it;
    for (it = rules->begin(); it != rules->end(); it++) {
        delete (*it).second;
    }
    
    delete rules;
}

void SGLSystem::draw(Matrix4 mat) {
    turtle->draw(mat);
}

void SGLSystem::generateLSystem(const string &lsystem, int depth) {
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
    pair<multimap<char, LSystemRule*>::iterator, 
         multimap<char, LSystemRule*>::iterator> ruleRange;
    
    ruleRange = rules->equal_range(variable);
    for (multimap<char, LSystemRule*>::iterator it = ruleRange.first;
            it != ruleRange.second; it++) {
        return (*it).second->rule;
    }
    
    cerr << "Error: rule not found" << endl;
    // Throw exception if rule not found
    throw(1);
}

bool SGLSystem::isVariable(char c) {
    return isupper(c);
}