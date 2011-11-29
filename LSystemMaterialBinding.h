/* 
 * File:   LSystemMaterialBinding.h
 * Author: tom
 *
 * Created on November 28, 2011, 2:32 PM
 */

#ifndef LSYSTEMMATERIALBINDING_H
#define	LSYSTEMMATERIALBINDING_H

#include "Material.h"

class LSystemMaterialBinding {
public:
    LSystemMaterialBinding(const Material &newMaterial, 
            double newBindThreshold);
    
    Material material;
    double bindThreshold;
};

#endif	/* LSYSTEMMATERIALBINDING_H */

