/* 
 * File:   SGNode.h
 * Author: tom
 *
 * Created on October 31, 2011, 5:23 PM
 */

#ifndef SGNODE_H
#define	SGNODE_H

#include "Matrix4.h"

class SGNode {
public:
    virtual void draw(Matrix4 mat)=0;
};

#endif	/* SGNODE_H */

