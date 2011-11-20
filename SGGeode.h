/* 
 * File:   SGGeode.h
 * Author: tom
 *
 * Created on October 31, 2011, 6:15 PM
 */

#ifndef SGGEODE_H
#define	SGGEODE_H

#include <GL/glut.h>
#include "SGNode.h"
#include "Material.h"

class SGGeode : public SGNode {
public:
    SGGeode(const Material &geodeMaterial);
    virtual ~SGGeode();
protected:
    Material material;
    void glVertex(const Vector3 &v);
    void glVertex(const Vector3 *v);
    void glNormal(const Vector3 &v);
    void glNormal(const Vector3 *v);
    void glTexture(const Vector3 &v);
    void glTexture(const Vector3 *v);
    void deleteVector3Array(Vector3 **array, int size);
};

#endif	/* SGGEODE_H */

