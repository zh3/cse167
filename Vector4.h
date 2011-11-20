#ifndef _VECTOR4_H_
#define _VECTOR4_H_

#include <ostream>

class Vector3;

class Vector4 {
    public:
    double x, y, z, o;
        Vector4(void);
        Vector4(double x0, double y0, double z0, double o0);
    
        void set(double x0, double y0, double z0, double o0);
        double get(int i);
        double getX(void);
        double getY(void);
        double getZ(void);
        double getO(void);

        void add(Vector4 &a);
        void add(Vector4 &a, Vector4 &b);

        void subtract(Vector4 &a);
        void subtract(Vector4 &a, Vector4 &b);

        void negate(void);
        void negate(Vector4 &a);

        void scale(double s);
        void scale(double s, Vector4 &a);

        double magnitude(void);
        void normalize(void);

        void dehomogenize(void);

        Vector3 toVector3(void) const;

        double &operator[](const int nIndex);
        Vector4 &operator+=(const Vector4 &a);
        Vector4 operator+(const Vector4 &a);
        Vector4 &operator-=(const Vector4 &a);
        Vector4 operator-(const Vector4 &a);

        friend std::ostream &operator<<(std::ostream &out, const Vector4 &a);
};

#endif
