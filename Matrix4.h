#ifndef _MATRIX4_H_
#define _MATRIX4_H_

#include "Vector4.h"
#include "Vector3.h"

class Matrix4
{
  protected:
    double m[4][4];   // matrix elements
    
  public:
    Matrix4();        // constructor
    Matrix4(double, double, double, double, double, double, double, double, 
            double, double, double, double, double, double, double, double);
    double* getPointer();  // return pointer to matrix elements

    void set(int row, int col, double n);
    double get(int row, int col) const;

    void multiply(Matrix4 &mat);
    Vector4 multiply(Vector4 &vec);
    Vector3 multiply(Vector3 &vec);

    // Make this matrix an identity matrix
    void toIdentity(void);
    // Make this a matrix for rotation about the X axis
    void toRotationMatrixX(double angle);
    // Make this a matrix for rotation about the Y axis
    void toRotationMatrixY(double angle);
    // Make this a matrix for rotation about the Z axis
    void toRotationMatrixZ(double angle);
    void toRotationMatrix(double angle, const Vector3 &axis);
    void toRotationMatrix(double angle, const Vector4 &axis);
    // Make this a matrix designed to scale a vectort
    void toScalingMatrix(double xFactor, double yFactor, double zFactor);
    // Create a matrix which will translate a vector by the x, y and z
    // differences specified
    void toTranslationMatrix(double dx, double dy, double dz);
    // Clear all matrix elements to zero
    void zero(void);
    
    void transpose(void);

    friend std::ostream &operator<<(std::ostream &out, const Matrix4 &a);
};

#endif