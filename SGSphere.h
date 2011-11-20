/* 
 * File:   SGSphere.h
 * Author: tom
 *
 * Created on November 1, 2011, 12:28 AM
 */

#ifndef SGSPHERE_H
#define	SGSPHERE_H

#include <GL/gl.h>
#include "SGGeode.h"

class SGSphere : public SGGeode {
public:
    SGSphere(const Material &material, GLdouble radius);
    virtual ~SGSphere();
    void draw(Matrix4 mat);
private:
    GLdouble radius;
    static const GLint nSlices;
    static const GLint nStacks;
};

#endif	/* SGSPHERE_H */

