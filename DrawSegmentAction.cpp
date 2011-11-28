/* 
 * File:   DrawSegmentAction.cpp
 * Author: tom
 * 
 * Created on November 27, 2011, 11:14 PM
 */

#include "DrawSegmentAction.h"
#include "SGTurtle.h"

DrawSegmentAction::DrawSegmentAction(double newSegmentSize) 
        : segmentSize(newSegmentSize) {
}

void DrawSegmentAction::doAction(SGTurtle *turtle) {
    turtle->drawMove(segmentSize);
}

