#include <ostream>
#include "BasicMath.h"
#include "Vector3.h"
#include <iostream>

using namespace std;

Vector3::Vector3(void) {
    set(0, 0, 0);
}

Vector3::Vector3(double x0, double y0, double z0) {
    set(x0, y0, z0);
}

void Vector3::set(double x0, double y0, double z0) {
    x = x0;
    y = y0;
    z = z0;
}

double Vector3::get(int i) {
    return (*this)[i];
}

double Vector3::getX(void) {
    return x;
}

double Vector3::getY(void) {
    return y;
}

double Vector3::getZ(void) {
    return z;
}

void Vector3::add(Vector3 &a) {
    (*this) += a;
}

void Vector3::add(Vector3 &a, Vector3 &b) {
    x = a.x + b.x;
    y = a.y + b.y;
    z = a.z + b.z;
}

void Vector3::subtract(Vector3 &a) {
    (*this) -= a;
}

void Vector3::subtract(Vector3 &a, Vector3 &b) {
    x = a.x - b.x;
    y = a.y - b.y;
    z = a.z - b.z;
}

void Vector3::negate(void) {
    x = -x;
    y = -y;
    z = -z;
}

void Vector3::negate(Vector3 &a) {
    x = -a.x;
    y = -a.y;
    z = -a.z;
}

void Vector3::scale(double s) {
    x *= s;
    y *= s;
    z *= s;
}

void Vector3::scale (double s, Vector3 &a) {
    x = s * a.x;
    y = s * a.y;
    z = s * a.z;
}

double Vector3::dot(Vector3 &a) {
    return x * a.x + y * a.y + z * a.z;
}

void Vector3::cross(Vector3 &a) {
    double x1 = y * a.z - z * a.y;
    double y1 = z * a.x - x * a.z;
    double z1 = x * a.y - y * a.x;
    
    x = x1;
    y = y1;
    z = z1;
}

void Vector3::cross(Vector3 &a, Vector3 &b) {
    x = a.y * b.z - a.z * b.y; 
    y = a.z * b.x - a.x * b.z; 
    z = a.x * b.y - a.y * b.x;
}

double Vector3::magnitude(void) {
    return sqrt(x * x + y * y + z * z);
}

void Vector3::normalize(void) {
    scale(1.0 / magnitude());
}

double &Vector3::operator[](const int nIndex) {
    switch (nIndex) {
    case 0:
        return x;
    case 1:
        return y;
    case 2:
        return z;
    default:
        throw nIndex;
    }
}

Vector3 &Vector3::operator+=(const Vector3 &a) {
    x += a.x;
    y += a.y;
    z += a.z;

    return (*this);
}

Vector3 Vector3::operator+(const Vector3 &a) {
    return Vector3(*this) += a;
}

Vector3 &Vector3::operator-=(const Vector3 &a) {
    x -= a.x;
    y -= a.y;
    z -= a.z;
    
    return (*this);
}

Vector3 Vector3::operator-(const Vector3 &a) {
    return Vector3(*this) -= a;
}

ostream &operator<<(ostream &out, const Vector3 &a) {
    out << "(" << a.x << " " << a.y << " " << a.z << ")";
    return out;
}
