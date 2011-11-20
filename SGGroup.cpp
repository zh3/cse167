/* 
 * File:   SGGroup.cpp
 * Author: tom
 * 
 * Created on October 31, 2011, 5:28 PM
 */

#include <vector>

#include "SGGroup.h"
using namespace std;

SGGroup::SGGroup() {
    children = new vector<SGNode *>();
}

SGGroup::SGGroup(const SGGroup& orig) {
    // TODO Not implemented
}

SGGroup::~SGGroup() {
    for (unsigned int i = 0; i < children->size(); i++) {
        delete children->at(i);
    }
    
    delete children;
}

void SGGroup::addChild(SGNode* child) {
    children->push_back(child);
}

void SGGroup::clearChildren() {
    for (unsigned int i = 0; i < children->size(); i++) {
        delete children->at(i);
    }
    
    children->clear();
}

bool SGGroup::removeChild(SGNode* child) {
    for (vector<SGNode *>::iterator i = children->begin(); i < children->end(); 
         i++) {
        if (*i == child) {
            children->erase(i);
            return true;
        }
    }
    
    return false;
}

