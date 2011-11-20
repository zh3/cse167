#include <ostream>
#include <stdio.h>
#include "BasicMath.h"
#include "Matrix4.h"

using namespace std;

Matrix4::Matrix4() {
    zero();
}

Matrix4::Matrix4(
    double m00, double m01, double m02, double m03,
    double m10, double m11, double m12, double m13,
    double m20, double m21, double m22, double m23,
    double m30, double m31, double m32, double m33 )
{
    set(0, 0, m00);
    set(0, 1, m01);
    set(0, 2, m02);
    set(0, 3, m03);
    set(1, 0, m10);
    set(1, 1, m11);
    set(1, 2, m12);
    set(1, 3, m13);
    set(2, 0, m20);
    set(2, 1, m21);
    set(2, 2, m22);
    set(2, 3, m23);
    set(3, 0, m30);
    set(3, 1, m31);
    set(3, 2, m32);
    set(3, 3, m33);
}

double* Matrix4::getPointer(void)
{
  return &m[0][0];
}

void Matrix4::toIdentity(void)
{
  double ident[4][4]={{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      set(i, j, ident[i][j]);
    }
  }
}

void Matrix4::set(int row, int col, double n) {
    // Matrix is stored as a column major array so reverse order of indexers
    m[col][row] = n;
}

double Matrix4::get(int row, int col) const {
    // Matrix is stored as a column major array so reverse order of indexers
    return m[col][row];
}

void Matrix4::multiply(Matrix4 &mat) {
    Matrix4 temp;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            double total = 0.0;
            for (int k = 0; k < 4; k++) {
                total += get(i, k) * mat.get(k, j);
            }
            temp.set(i, j, total);
        }
    }

    (*this) = temp;
}

Vector4 Matrix4::multiply(Vector4 &vec) {
    Vector4 v;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            v[i] += get(i, j) * vec[j];
        }
    }

    return v;
}

Vector3 Matrix4::multiply(Vector3& vec) {
    Vector4 v(vec.x, vec.y, vec.z, 1.0);
    Vector4 multipliedRes(multiply(v));
    multipliedRes.dehomogenize();

    return Vector3(multipliedRes.x, multipliedRes.y, multipliedRes.z);
}

// angle in degrees
void Matrix4::toRotationMatrixX(double angle) {
    double th = BasicMath::radian(angle);
    zero();
    set(0, 0, 1.0);
    set(1, 1, cos(th));
    set(1, 2, -sin(th));
    set(2, 1, sin(th));
    set(2, 2, cos(th));
    set(3, 3, 1.0);
}

// angle in degrees
void Matrix4::toRotationMatrixY(double angle) {
    double th = BasicMath::radian(angle);
    set(0, 0, cos(th));
    set(0, 1, 0.0);
    set(0, 2, sin(th));
    set(0, 3, 0.0);
    set(1, 0, 0.0);
    set(1, 1, 1.0);
    set(1, 2, 0.0);
    set(1, 3, 0.0);
    set(2, 0, -sin(th));
    set(2, 1, 0.0);
    set(2, 2, cos(th));
    set(2, 3, 0.0);
    set(3, 0, 0.0);
    set(3, 1, 0.0);
    set(3, 2, 0.0);
    set(3, 3, 1.0);
}

// angle in degrees
void Matrix4::toRotationMatrixZ(double angle) {
    double th = BasicMath::radian(angle);
    zero();
    set(0, 0, cos(th));
    set(0, 1, -sin(th));
    set(1, 0, sin(th));
    set(1, 1, cos(th));
    set(2, 2, 1.0);
    set(3, 3, 1.0);
}

// angle in degrees
void Matrix4::toRotationMatrix(double angle, const Vector4 &axis) {
    Vector4 a(axis);
    toRotationMatrix(angle, a.toVector3());
}

// angle in degrees
void Matrix4::toRotationMatrix(double angle, const Vector3 &axis) {
    // Make the x,y,z component specification of the axis a unit vector
    Vector3 a(axis);
    a.normalize();

    double th = BasicMath::radian(angle);
    set(0, 0, 1.0 + (1.0 - cos(th)) * (a.x * a.x - 1.0));
    set(0, 1, -a.z * sin(th) + (1.0 - cos(th)) * a.x * a.y);
    set(0, 2, a.y * sin(th) + (1.0 - cos(th)) * a.x * a.z);
    set(0, 3, 0.0);
    set(1, 0, a.z * sin(th) + (1.0 - cos(th)) * a.y * a.x);
    set(1, 1, 1.0 + (1.0 - cos(th)) * (a.y * a.y - 1.0));
    set(1, 2, -a.x * sin(th) + (1.0 - cos(th)) * a.y * a.z);
    set(1, 3, 0.0);
    set(2, 0, -a.y * sin(th) + (1.0 - cos(th)) * a.z * a.x);
    set(2, 1, a.x * sin(th) + (1.0 - cos(th)) * a.z * a.y);
    set(2, 2, 1.0 + (1.0 - cos(th)) * (a.z * a.z - 1));
    set(2, 3, 0.0);
    set(3, 0, 0.0);
    set(3, 1, 0.0);
    set(3, 2, 0.0);
    set(3, 3, 1.0);
}

void Matrix4::toScalingMatrix(double xFactor, double yFactor,
        double zFactor) {
    zero();
    set(0, 0, xFactor);
    set(1, 1, yFactor);
    set(2, 2, zFactor);
    set(3, 3, 1.0);
}

void Matrix4::toTranslationMatrix(double dx, double dy, double dz) {
    toIdentity();
    set(0, 3, dx);
    set(1, 3, dy);
    set(2, 3, dz);
    set(3, 3, 1.0);
}

void Matrix4::zero(void) {
   for (int i=0; i<4; ++i) {
    for (int j=0; j<4; ++j) {
      set(i, j, 0.0);
    }
  }
}

void Matrix4::transpose(void) {
    Matrix4 temp;
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            temp.set(j, i, get(i, j));
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            set(i, j, temp.get(i, j));
        }
    }
}

ostream &operator<<(ostream &out, const Matrix4 &a) {
    out << "(" << endl;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%4.2f ", a.get(i, j));
        }

        out << endl;
    }
    
    return out;
}
