#include <cstdio>

#ifndef OBJECT
#define OBJECT
#define square(x) ((x) * (x))
const double eps = 1e-5;

class Vec3{
public:
    double x, y, z;
    Vec3(double _x=0, double _y=0, double _z=0);
    Vec3 operator + (const Vec3& a) const;
    Vec3 operator - (const Vec3& a) const;
    Vec3 operator * (const Vec3& a) const;
    Vec3 operator * (double a) const;
    Vec3 operator / (double a) const;
    Vec3 det(const Vec3& a) const;
    double dot(const Vec3& a) const;
    double norm2();
    Vec3& normal();
};

class Line3{
public:
    Vec3 o, d;
    Line3(Vec3 _o=Vec3(), Vec3 _d=Vec3());
};

enum Refl_type {DIFF, SPEC, REFR};
class Object{
public:
    Vec3 e, c;
    Refl_type refl;
    Object(Vec3 _e=Vec3(), Vec3 _c=Vec3(), Refl_type _refl=DIFF);
    virtual double intersect(const Line3 &ray) const;
    virtual Vec3 get_norm(const Vec3& x) const;
};


class Sphere :public Object{
public:
    Vec3 o;
    double rad;
    Sphere(double _rad=0, Vec3 _o=Vec3(), Vec3 _e=Vec3(), Vec3 _c=Vec3(), Refl_type _refl=DIFF);
    double intersect(const Line3 &ray) const;
    Vec3 get_norm(const Vec3& x) const;
};

#endif