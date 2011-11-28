/* 
 * File:   DrawSegmentAction.h
 * Author: tom
 *
 * Created on November 27, 2011, 11:14 PM
 */

#ifndef DRAWSEGMENTACTION_H
#define	DRAWSEGMENTACTION_H

#include "TurtleAction.h"

class DrawSegmentAction : public TurtleAction {
public:
    DrawSegmentAction(double newSegmentSize);
    void doAction(SGTurtle *turtle);
private:
    double segmentSize;
};

#endif	/* DRAWSEGMENTACTION_H */

