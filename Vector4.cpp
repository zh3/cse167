#include <ostream>
#include "BasicMath.h"
#include "Vector4.h"
#include "Vector3.h"
#include <iostream>

using namespace std;

Vector4::Vector4(void) {
    set(0, 0, 0, 0);
}

Vector4::Vector4(double x0, double y0, double z0, double o0) {
    set(x0, y0, z0, o0);
}

void Vector4::set(double x0, double y0, double z0, double o0) {
    x = x0;
    y = y0;
    z = z0;
    o = o0;
}

double Vector4::get(int i) {
    return (*this)[i];
}

double Vector4::getX(void) {
    return x;
}

double Vector4::getY(void) {
    return y;
}

double Vector4::getZ(void) {
    return z;
}

double Vector4::getO(void) {
    return o;
}

void Vector4::add(Vector4 &a) {
    (*this) += a;
}

void Vector4::add(Vector4 &a, Vector4 &b) {
    x = a.x + b.x;
    y = a.y + b.y;
    z = a.z + b.z;
    o = a.o + b.o;
}

void Vector4::subtract(Vector4 &a) {
    (*this) -= a;
}

void Vector4::subtract(Vector4 &a, Vector4 &b) {
    x = a.x - b.x;
    y = a.y - b.y;
    z = a.z - b.z;
    o = a.o - b.o;
}

void Vector4::negate(void) {
    x = -x;
    y = -y;
    z = -z;
    o = -o;
}

void Vector4::negate(Vector4 &a) {
    x = -a.x;
    y = -a.y;
    z = -a.z;
    o = -a.o;
}

void Vector4::scale(double s) {
    x *= s;
    y *= s;
    z *= s;
    o *= s;
}

void Vector4::scale (double s, Vector4 &a) {
    x = s * a.x;
    y = s * a.y;
    z = s * a.z;
    o = s * a.o;
}

double Vector4::magnitude(void) {
    return sqrt(x * x + y * y + z * z + o * o);
}

void Vector4::normalize(void) {
    scale(1.0 / magnitude());
}

void Vector4::dehomogenize(void) {
    scale(1.0 / o);
}

Vector3 Vector4::toVector3(void) const {
    return Vector3(x, y, z);
}

double &Vector4::operator[](const int nIndex) {
    switch (nIndex) {
    case 0:
        return x;
    case 1:
        return y;
    case 2:
        return z;
    case 3:
        return o;
    default:
        throw nIndex;
    }
}

Vector4 &Vector4::operator+=(const Vector4 &a) {
    x += a.x;
    y += a.y;
    z += a.z;
    o += a.o;

    return (*this);
}

Vector4 Vector4::operator+(const Vector4 &a) {
    return Vector4(*this) += a;
}

Vector4 &Vector4::operator-=(const Vector4 &a) {
    x -= a.x;
    y -= a.y;
    z -= a.z;
    o -= a.o;
    
    return (*this);
}

Vector4 Vector4::operator-(const Vector4 &a) {
    return Vector4(*this) -= a;
}

ostream &operator<<(ostream &out, const Vector4 &a) {
    out << "(" << a.x << " " << a.y << " " << a.z <<  " " << a.o << ")";
    return out;
}
