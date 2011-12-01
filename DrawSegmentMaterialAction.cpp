/* 
 * File:   DrawSegmentMaterialAction.cpp
 * Author: tom
 * 
 * Created on November 30, 2011, 10:25 PM
 */

#include "DrawSegmentMaterialAction.h"

DrawSegmentMaterialAction::DrawSegmentMaterialAction(Material &newMaterial, 
        double newSegmentSize)
        : material(newMaterial), segmentSize(newSegmentSize){
}

void DrawSegmentMaterialAction::doAction(SGTurtle* turtle) {
    Material prevMaterial(turtle->getMaterial());
    
    turtle->setMaterial(material);
    turtle->drawMove(segmentSize);
    turtle->setMaterial(prevMaterial);
}

