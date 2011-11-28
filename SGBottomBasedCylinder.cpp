/* 
 * File:   SGBottomBasedCylinder.cpp
 * Author: tom
 * 
 * Created on November 1, 2011, 11:47 PM
 */

#include "SGBottomBasedCylinder.h"
#include "BasicMath.h"

const GLint SGBottomBasedCylinder::nSegments = 8;
using namespace std;

SGBottomBasedCylinder::SGBottomBasedCylinder(const Material &material, GLdouble newRadius, 
        GLdouble newHeight) : SGGeode(material), radius(newRadius), 
        height(newHeight) {
    generateCylinder(radius, height);
}

SGBottomBasedCylinder::~SGBottomBasedCylinder() {
    deleteVertexVector(triangleVertices);
    deleteVertexVector(quadVertices);
    deleteVertexVector(triangleNormals);
    deleteVertexVector(quadNormals);
}

void SGBottomBasedCylinder::draw(Matrix4 mat) {
    material.apply();
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    //glLoadMatrixd(mat.getPointer());
    glMultMatrixd(mat.getPointer());
    
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    drawCylinder();
    glPopMatrix();
}

void SGBottomBasedCylinder::generateCylinder(double radius, double height) {
    triangleVertices = new vector<Vector3 *>();
    quadVertices = new vector<Vector3 *>();
    triangleNormals = new vector<Vector3 *>();
    quadNormals = new vector<Vector3 *>();
    
    double x1, y1, x2, y2;
    
    double segmentAngle = (2 * BasicMath::PI) / nSegments;
    for (double t = 0; t < 2 * BasicMath::PI; t += segmentAngle) {
        x1 = radius * cos(t);
        y1 = radius * sin(t);
        
        x2 = radius * cos(t + segmentAngle);
        y2 = radius * sin(t + segmentAngle);
        
        Vector3 *v0 = new Vector3(0.0, 0.0, height);
        Vector3 *v1 = new Vector3(x1, y1, height);
        Vector3 *v2 = new Vector3(x2, y2, height);
        triangleVertices->push_back(v0);
        triangleVertices->push_back(v1);
        triangleVertices->push_back(v2);
        Vector3 v0v1(*v1 - *v0);
        Vector3 v0v2(*v2 - *v0);
        v0v1.cross(v0v2);
        v0v1.normalize();
        
        Vector3 *upperTriangleNormal1 = new Vector3(v0v1);
        Vector3 *upperTriangleNormal2 = new Vector3(v0v1);
        Vector3 *upperTriangleNormal3 = new Vector3(v0v1);
        
        triangleNormals->push_back(upperTriangleNormal1);
        triangleNormals->push_back(upperTriangleNormal2);
        triangleNormals->push_back(upperTriangleNormal3);
        
        v0 = new Vector3(0.0, 0.0, 0.0);
        v1 = new Vector3(x2, y2, 0.0);
        v2 = new Vector3(x1, y1, 0.0);
        triangleVertices->push_back(v0);
        triangleVertices->push_back(v1);
        triangleVertices->push_back(v2);
        
        v0v1 = (*v1 - *v0);
        v0v2 = (*v2 - *v0);
        v0v1.cross(v0v2);
        v0v1.normalize();
        
        upperTriangleNormal1 = new Vector3(v0v1);
        upperTriangleNormal2 = new Vector3(v0v1);
        upperTriangleNormal3 = new Vector3(v0v1);
        triangleNormals->push_back(upperTriangleNormal1);
        triangleNormals->push_back(upperTriangleNormal2);
        triangleNormals->push_back(upperTriangleNormal3);
        
        Vector3 *q0 = new Vector3(x1, y1, height);
        Vector3 *q1 = new Vector3(x1, y1, 0.0);
        Vector3 *q2 = new Vector3(x2, y2, 0.0);
        Vector3 *q3 = new Vector3(x2, y2, height);
        
        Vector3 q1q0(*q0 - *q1);
        Vector3 q1q2(*q2 - *q1);
        q1q2.cross(q1q0);
        q1q2.normalize();
        
        Vector3 *quadNormal1 = new Vector3(q1q2);
        Vector3 *quadNormal2 = new Vector3(q1q2);
        Vector3 *quadNormal3 = new Vector3(q1q2);
        Vector3 *quadNormal4 = new Vector3(q1q2);
        quadNormals->push_back(quadNormal1);
        quadNormals->push_back(quadNormal2);
        quadNormals->push_back(quadNormal3);
        quadNormals->push_back(quadNormal4);
        quadVertices->push_back(q0);
        quadVertices->push_back(q1);
        quadVertices->push_back(q2);
        quadVertices->push_back(q3);
    }
}

void SGBottomBasedCylinder::drawCylinder() {
    glBegin(GL_TRIANGLES);
    for (unsigned int i = 0; i < triangleVertices->size(); i++) {
        Vector3 *vertex = triangleVertices->at(i);
        Vector3 *normal = triangleNormals->at(i);
        glNormal3d(normal->x, normal->y, normal->z);
        glVertex3d(vertex->x, vertex->y, vertex->z);
    }
    glEnd();
    
    glBegin(GL_QUADS);
    for (unsigned int i = 0; i < quadVertices->size(); i++) {
        Vector3 *vertex = quadVertices->at(i);
        Vector3 *normal = quadNormals->at(i);
        glNormal3d(normal->x, normal->y, normal->z);
        glVertex3d(vertex->x, vertex->y, vertex->z);
    }
    glEnd();
}

void SGBottomBasedCylinder::deleteVertexVector(vector<Vector3 *> *vector) {
    for (unsigned int i = 0; i < vector->size(); i++) {
        delete vector->at(i);
    }
    
    delete vector;
}
