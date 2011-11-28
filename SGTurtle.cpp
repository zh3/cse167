/* 
 * File:   SGTurtle.cpp
 * Author: tom
 * 
 * Created on November 27, 2011, 12:26 PM
 */

#include "SGTurtle.h"
#include <GL/glut.h>
#include <iostream>

using namespace std;

SGTurtle::SGTurtle(const Material &material,
        const Vector3& newH, const Vector3 & newL, const Vector3 & newU, 
        const Vector3 & newUp, const Vector3 & newOrigin)
        : SGGeode(material),
          h(newH), l(newL), u(newU), 
          hRotation(0.0), lRotation(0.0), uRotation(0.0),
          up(newUp), origin(newOrigin), 
          vertices(new vector<Vector3 *>()),
          states(new stack<TurtleState *>()) {
    normalizeVectors();
}

SGTurtle::SGTurtle(const Material &material) 
        : SGGeode(material),
          h(0.0, 0.0, -1.0), l(-1.0, 0.0, 0.0), u(0.0, 1.0, 0.0), 
          hRotation(0.0), lRotation(0.0), uRotation(0.0),
          up(1.0, 0.0, 0.0), origin(0.0, 0.0, 0.0),
          vertices(new vector<Vector3 *>()),
          states(new stack<TurtleState *>()){
    normalizeVectors();
}

SGTurtle::~SGTurtle() {
    for (unsigned int i = 0; i < vertices->size(); i++) {
        delete vertices->at(i);
    }
    
    while (!states->empty()) {
        delete states->top();
        states->pop();
    }
    
    delete states;
    delete vertices;
}

void SGTurtle::move(double distance) {
    Matrix4 turtleMatrix(getTurtleMatrix());
    Vector3 endPoint(up);
    endPoint.scale(distance);
    
    origin = turtleMatrix.multiply(endPoint);
}

void SGTurtle::drawMove(double distance) {
    Matrix4 turtleMatrix(getTurtleMatrix());
    Vector3 turtleOrigin(0.0, 0.0, 0.0);
    Vector3 turtleUp(up);
    turtleUp.scale(distance);
    
    Vector3 turtleEndpoint(turtleOrigin + turtleUp);
    
    Vector3 *start = new Vector3(turtleMatrix.multiply(turtleOrigin));
    Vector3 *end = new Vector3(turtleMatrix.multiply(turtleEndpoint));
    
    vertices->push_back(start);
    vertices->push_back(end);
    
    origin = turtleMatrix.multiply(turtleEndpoint);
}
    
void SGTurtle::rotateH(double angle) {
    hRotation += angle;
    
    Matrix4 rotation;
    rotation.toRotationMatrixX(angle);
    
    Matrix4 turtleBasisRotationMatrix(getTurtleBasisRotationMatrix());
    turtleBasisRotationMatrix.multiply(rotation);
    setBasisRotation(turtleBasisRotationMatrix);
}

void SGTurtle::rotateL(double angle) {
    lRotation += angle;
    
    Matrix4 rotation;
    rotation.toRotationMatrixY(angle);
    
    Matrix4 turtleBasisRotationMatrix(getTurtleBasisRotationMatrix());
    turtleBasisRotationMatrix.multiply(rotation);
    setBasisRotation(turtleBasisRotationMatrix);
}

void SGTurtle::rotateU(double angle) {
    uRotation += angle;
    
    Matrix4 rotation;
    rotation.toRotationMatrixZ(angle);
    
    Matrix4 turtleBasisRotationMatrix(getTurtleBasisRotationMatrix());
    turtleBasisRotationMatrix.multiply(rotation);
    setBasisRotation(turtleBasisRotationMatrix);
}

void SGTurtle::pushState() {
    TurtleState *currentState = new TurtleState(h, l, u, origin);
    
    states->push(currentState);
}

void SGTurtle::popState() {
    TurtleState *state = states->top();
    
    states->pop();
    h = state->h;
    l = state->l;
    u = state->u;
    
    origin = state->origin;
}

void SGTurtle::draw(Matrix4 mat) {
    glColor3f(1.0, 0.0, 0.0);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMultMatrixd(mat.getPointer());
    
    glBegin(GL_LINES);
    for (unsigned int i = 0; i < vertices->size(); i++) {
        //cout << "vertex " << i << " is " << *vertices->at(i) << endl;
        glVertex(vertices->at(i));
    }
    glEnd();
    
    glPopMatrix();
}

void SGTurtle::normalizeVectors() {
    h.normalize();
    l.normalize();
    u.normalize();
    
    up.normalize();
}

Matrix4 SGTurtle::getTurtleMatrix() {
    return Matrix4(
            h.x, l.x, u.x, origin.x,
            h.y, l.y, u.y, origin.y,
            h.z, l.z, u.z, origin.z,
            0.0, 0.0, 0.0, 1.0
           );
}

Matrix4 SGTurtle::getTurtleBasisRotationMatrix() {
    return Matrix4(
            h.x, l.x, u.x, 0.0,
            h.y, l.y, u.y, 0.0,
            h.z, l.z, u.z, 0.0,
            0.0, 0.0, 0.0, 1.0
           );
}

void SGTurtle::setBasis(const Matrix4& turtleMatrix) {
    h.x = turtleMatrix.get(0, 0);
    h.y = turtleMatrix.get(1, 0);
    h.z = turtleMatrix.get(2, 0);
    
    l.x = turtleMatrix.get(0, 1);
    l.y = turtleMatrix.get(1, 1);
    l.z = turtleMatrix.get(2, 1);
    
    u.x = turtleMatrix.get(0, 2);
    u.x = turtleMatrix.get(1, 2);
    u.x = turtleMatrix.get(2, 2);
    
    origin.x = turtleMatrix.get(0, 3);
    origin.y = turtleMatrix.get(1, 3);
    origin.z = turtleMatrix.get(2, 3);
}

void SGTurtle::setBasisRotation(const Matrix4& turtleMatrix) {
    h.x = turtleMatrix.get(0, 0);
    h.y = turtleMatrix.get(1, 0);
    h.z = turtleMatrix.get(2, 0);
    
    l.x = turtleMatrix.get(0, 1);
    l.y = turtleMatrix.get(1, 1);
    l.z = turtleMatrix.get(2, 1);
    
    u.x = turtleMatrix.get(0, 2);
    u.y = turtleMatrix.get(1, 2);
    u.z = turtleMatrix.get(2, 2);
}

