/* 
 * File:   SGTurtle.h
 * Author: tom
 *
 * Created on November 27, 2011, 12:26 PM
 */

#ifndef SGTURTLE_H
#define	SGTURTLE_H

#include "Vector3.h"
#include "BasicMath.h"
#include "Matrix4.h"
#include "Vector4.h"
#include "SGGeode.h"
#include "TurtleState.h"
#include <vector>
#include <stack>

class SGTurtle : public SGGeode {
public:
    SGTurtle(const Material &material, 
            const Vector3& newH, const Vector3 & newL, const Vector3 & newU, 
            const Vector3 & newUp, const Vector3 & newOrigin);
    SGTurtle(const Material &material);
    virtual ~SGTurtle();
    
    void move(double distance);
    void drawMove(double distance);
    
    void rotateH(double angle);
    void rotateL(double angle);
    void rotateU(double angle);
    
    void pushState();
    void popState();
    
    void draw(Matrix4 mat);
private:
    Vector3 h;
    Vector3 l;
    Vector3 u;
    double hRotation;
    double lRotation;
    double uRotation;
    
    Vector3 up;
    Vector3 origin;
    
    std::vector<Vector3 *> *vertices;
    std::stack<TurtleState *> *states;
    
    void normalizeVectors();
    Matrix4 getTurtleMatrix();
    Matrix4 getTurtleBasisRotationMatrix();
    void setBasis(const Matrix4 &turtleMatrix);
    void setBasisRotation(const Matrix4 &turtleMatrix);
};

#endif	/* SGTURTLE_H */

