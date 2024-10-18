#include "object.h"

#ifndef CANVAS
#define CANVAS

class Canvas{
public:
    Canvas(int _n, Sphere* _objects, Line3 _camera, char* _path);
    Canvas();
    // ~Canvas();
    Vec3 radiance(const Line3 &l, int depth, unsigned short * seed);
    inline bool get_intersect(const Line3 &l, double& t, int& id);
    void render(int samples, int w, int h, double d, double ratio);
// private:
    int n;
    Object **objects;
    const char* path;
    Line3 camera;
};

#endif