/* 
 * File:   SGGroup.h
 * Author: tom
 *
 * Created on October 31, 2011, 5:28 PM
 */

#ifndef SGGROUP_H
#define	SGGROUP_H

#include <vector>
#include "SGNode.h"

class SGGroup : public SGNode {
public:
    SGGroup();
    SGGroup(const SGGroup& orig);
    virtual ~SGGroup();
    void addChild(SGNode *child);
    void clearChildren();
    bool removeChild(SGNode *child);
protected:
    std::vector<SGNode *> *children;
};

#endif	/* SGGROUP_H */

