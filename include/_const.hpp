//
// Created by ZzyPC on 2021/6/8.
//
#include <cmath>

#define max3(x, y, z) (x > y && x > z ? x : y > z ? y : z)
const double PI = acos(-1);
const double inf_db = 1e20;
inline double clamp(double x){
    return x < 0 ? 0 : x > 1 ? 1 : x;
}
inline int toInt(double x) {
    return int( clamp(x) * 255 + .5);
}
