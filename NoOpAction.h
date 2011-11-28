/* 
 * File:   NoOpAction.h
 * Author: tom
 *
 * Created on November 27, 2011, 11:37 PM
 */

#ifndef NOOPACTION_H
#define	NOOPACTION_H

#include "TurtleAction.h"

class NoOpAction : public TurtleAction {
public:
    void doAction(SGTurtle *turtle);
};

#endif	/* NOOPACTION_H */

