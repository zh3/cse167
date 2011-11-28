/* 
 * File:   LSystemRule.h
 * Author: tom
 *
 * Created on November 27, 2011, 8:19 PM
 */

#ifndef LSYSTEMRULE_H
#define	LSYSTEMRULE_H

#include <string>

class LSystemRule {
public:
    LSystemRule(std::string newRule, double newProbability);
    
    std::string rule;
    double probability;
};

#endif	/* LSYSTEMRULE_H */

