/* 
 * File:   SGBottomBasedCylinder.h
 * Author: tom
 *
 * Created on November 1, 2011, 11:47 PM
 */

#ifndef SGBOTTOMBASEDCYLINDER_H
#define	SGBOTTOMBASEDCYLINDER_H

#include <GL/glut.h>
#include <vector>
#include "SGGeode.h"

class SGBottomBasedCylinder : public SGGeode {
public:
    SGBottomBasedCylinder(const Material &material, GLdouble newRadius, 
               GLdouble newHeight);
    virtual ~SGBottomBasedCylinder();
    
    void draw(Matrix4 mat);
private:
    static const GLint nSegments;
    GLdouble radius;
    GLdouble height;
    std::vector<Vector3 *> *triangleVertices;
    std::vector<Vector3 *> *quadVertices;
    std::vector<Vector3 *> *triangleNormals;
    std::vector<Vector3 *> *quadNormals;
    
    void generateCylinder(double radius, double height);
    void drawCylinder();
    void deleteVertexVector(std::vector<Vector3 *> *vector);
};

#endif	/* SGBOTTOMBASEDCYLINDER_H */

