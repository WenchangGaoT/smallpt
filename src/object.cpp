#include "../include/object.h"
#include <math.h>

Vec3 :: Vec3(double _x, double _y, double _z):x(_x), y(_y), z(_z){}
Vec3 Vec3 :: operator + (const Vec3& a) const{
    return Vec3(x + a.x, y + a.y, z + a.z);
}
Vec3 Vec3 :: operator - (const Vec3& a) const {
    return Vec3(x - a.x, y - a.y, z - a.z);
}
Vec3 Vec3 :: operator * (const Vec3& a) const{
    return Vec3(x * a.x, y * a.y, z * a.z);
}
Vec3 Vec3 :: operator * (double a) const {
    return Vec3(x * a, y * a, z * a);
}
Vec3 Vec3 :: operator / (double a) const {
    return Vec3(x / a, y / a, z / a);
}
Vec3 Vec3 :: det(const Vec3& a) const {
    return Vec3(y * a.z - z * a.y,  z * a.x - x * a.z,  x * a.y - y * a.x);
}
double Vec3 :: dot(const Vec3& a) const {
    return x * a.x + y * a.y + z * a.z;
}
double Vec3::norm2() {
    return sqrt(x * x + y * y + z * z);
}
Vec3& Vec3 ::normal() {
    double l = sqrt(x * x + y * y + z * z);
    x /= l, y /= l, z /= l;
    return *this;
}


Line3::Line3(Vec3 _o, Vec3 _d):o(_o), d(_d){}


Object::Object (Vec3 _e, Vec3 _c, Refl_type _refl):
e(_e), c(_c), refl(_refl){}
double Object::intersect(const Line3 &ray) const{
    return 0;
};
Vec3 Object::get_norm(const Vec3 &x) const {
    return Vec3();
}


Sphere::Sphere(double _rad, Vec3 _o, Vec3 _e, Vec3 _c, Refl_type _refl):
 Object(_e, _c, _refl), rad(_rad), o(_o){}
double Sphere::intersect(const Line3 &ray) const {
    Vec3 P = o - ray.o;
    double t = 0, a = P.dot(ray.d), l2 = P.dot(P);
    double intc = square(rad) + square(a) - l2;
    if (intc <= 0) return 0;
    intc = sqrt(intc);
    if((t = a - intc) > eps || (t = a + intc) > eps) return t;
    else return 0;
}
Vec3 Sphere::get_norm(const Vec3 &x) const {
    return (x - o).normal();
}