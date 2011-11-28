/* 
 * File:   TurtleState.h
 * Author: tom
 *
 * Created on November 27, 2011, 5:07 PM
 */

#ifndef TURTLESTATE_H
#define	TURTLESTATE_H
#include "Vector3.h"

class TurtleState {
public:
    TurtleState(const Vector3 &turtleH, const Vector3 &turtleL, 
            const Vector3 &turtleU, const Vector3 &turtleOrigin);
    
    Vector3 h;
    Vector3 l;
    Vector3 u;
    Vector3 origin;
};

#endif	/* TURTLESTATE_H */

