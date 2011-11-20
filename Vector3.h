#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include <ostream>

class Vector3 {
    public:
        double x, y, z;
        Vector3(void);
        Vector3(double x0, double y0, double z0);
    
        void set(double x0, double y0, double z0);
        double get(int i);
        double getX(void);
        double getY(void);
        double getZ(void);

        void add(Vector3 &a);
        void add(Vector3 &a, Vector3 &b);

        void subtract(Vector3 &a);
        void subtract(Vector3 &a, Vector3 &b);

        void negate(void);
        void negate(Vector3 &a);

        void scale(double s);
        void scale(double s, Vector3 &a);

        double dot(Vector3 &a);
        void cross(Vector3 &a);
        void cross(Vector3 &a, Vector3 &b);

        double magnitude(void);
        void normalize(void);

        double &operator[](const int nIndex);
        Vector3 &operator+=(const Vector3 &a);
        Vector3 operator+(const Vector3 &a);
        Vector3 &operator-=(const Vector3 &a);
        Vector3 operator-(const Vector3 &a);

        friend std::ostream &operator<<(std::ostream &out, const Vector3 &a);
};

#endif
