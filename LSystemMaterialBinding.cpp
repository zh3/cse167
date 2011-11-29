/* 
 * File:   LSystemMaterialBinding.cpp
 * Author: tom
 * 
 * Created on November 28, 2011, 2:32 PM
 */

#include "LSystemMaterialBinding.h"

LSystemMaterialBinding::LSystemMaterialBinding(const Material &newMaterial, 
            double newBindThreshold)  
                : material(newMaterial), bindThreshold(newBindThreshold) {
    if (bindThreshold < 0.0 || bindThreshold > 1.0) throw (bindThreshold);
}

