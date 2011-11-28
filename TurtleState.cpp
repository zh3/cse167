/* 
 * File:   TurtleState.cpp
 * Author: tom
 * 
 * Created on November 27, 2011, 5:07 PM
 */

#include "TurtleState.h"

TurtleState::TurtleState(const Vector3 &turtleH, const Vector3 &turtleL, 
            const Vector3 &turtleU, const Vector3 &turtleOrigin)
        : h(turtleH), l(turtleL), u(turtleU), origin(turtleOrigin) {
}

