/* 
 * File:   TurtleAction.h
 * Author: tom
 *
 * Created on November 27, 2011, 11:04 PM
 */

#ifndef TURTLEACTION_H
#define	TURTLEACTION_H

#include "SGTurtle.h"

class TurtleAction {
public:
    virtual void doAction(SGTurtle *turtle) = 0;
};

#endif	/* TURTLEACTION_H */

