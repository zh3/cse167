/* 
 * File:   DrawSegmentMaterialAction.h
 * Author: tom
 *
 * Created on November 30, 2011, 10:25 PM
 */

#ifndef DRAWSEGMENTMATERIALACTION_H
#define	DRAWSEGMENTMATERIALACTION_H

#include "TurtleAction.h"
#include "Material.h"

class DrawSegmentMaterialAction : public TurtleAction {
public:
    DrawSegmentMaterialAction(Material &newMaterial, double newSegmentSize);
    void doAction(SGTurtle *turtle);
private:
    Material material;
    double segmentSize;
};

#endif	/* DRAWSEGMENTMATERIALACTION_H */

