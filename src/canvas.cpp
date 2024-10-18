#include "../include/_const.hpp"
#include "../include/_random.h"
#include "../include/object.h"
#include "../include/canvas.h"
#include <cmath>

Canvas::Canvas():n(0), objects(nullptr){}
Canvas::Canvas(int _n, Sphere* _objects, Line3 _camera, char* _path):n(_n), camera(_camera){
    n = _n;
    objects = new Object* [n];
    for (int i = 0; i < n; ++i) {
        objects[i] = &_objects[i];
    }
    path = _path;
}
// Canvas::~Canvas() {
//     // delete[] objects;
//     // delete[] path;
// }

// return true if intersected with something, and id is set to its id
inline bool Canvas::get_intersect(const Line3 &l, double &t, int &id) {
    double d;
    t = inf_db;
    for(int i = 0; i < n; ++i) {
        d = objects[i]->intersect(l);
        if(d != 0 && d < t) {
            t = d, id = i;
        }
    }
    return t < inf_db;
}

// sampling with constraints
Vec3 Canvas::radiance(const Line3 &l, int depth, unsigned short *seed) {
    depth++;
    int id = 0;
    double t;
    if(!get_intersect(l, t, id)) {
        return Vec3();
    }
    Object* obj = nullptr;
    obj = objects[id];
    Vec3 x = l.o + l.d * t, _n = obj->get_norm(x), nl = l.d.dot(_n) < 0 ? _n : _n * -1, clr = obj->c;
    double p = max3(clr.x, clr.y, clr.z);
    if(depth > 5) {
        if (rnd::erand48(seed) < p && depth < 10) {
            clr.x /= p, clr.y /= p, clr.z /= p;
        }
        else {
            return obj->e;
        }
    }
    if(obj->refl == DIFF) {
        double phi = PI * rnd::erand48(seed) / 2, theta = 2 * PI * rnd::erand48(seed), sin_phi = sin(phi);
        const Vec3& w = nl;
        Vec3 u = ((fabs(w.x) > .9 ? Vec3(0, 1, 0) : Vec3(1, 0, 0)).det(w)).normal(), v = w.det(u);
        Vec3 r = (u * sin_phi * cos(theta) + v * sin_phi * sin(theta) +  w * sqrt(1 - square(sin_phi))).normal();
        return obj->e + clr * radiance(Line3(x, r), depth, seed);
    }
    else if(obj->refl == SPEC){
        return obj->e + clr * radiance(Line3(x, l.d - nl * 2 * l.d.dot(nl)), depth, seed);
    }
    else if(obj->refl == REFR) {
        Line3  refL(x, l.d - nl * 2 * l.d.dot(nl));
        bool into = _n.dot(nl) > 0;
        double nc = 1.0, nt = 1.5, N = into? (nc / nt) : (nt / nc), cos_theta1 = -l.d.dot(nl);
        double cos2_theta2 = 1 - N * N * (1 - cos_theta1 * cos_theta1);
        if(cos2_theta2 <= 0) {
            return obj->e + clr * radiance(refL, depth, seed);
        }
        Vec3 d_fra = (l.d * N - nl * (-cos_theta1 * N  + sqrt(cos2_theta2))).normal();
        double F0 = square(nt - nc) / square(nt + nc), c = (1 - (into ? cos_theta1 : d_fra.dot(_n))); 
        double Re = F0 + (1 - F0) * c * c * c * c * c, Tr = 1 - Re; 
        if(depth > 2) {
            double P = .25 + .5 * Re, RP = Re / P, TP = Tr / (1 - P);
            return obj->e + clr * (rnd::erand48(seed) < P ? radiance(refL, depth, seed) * RP : radiance(Line3(x, d_fra), depth, seed) * TP);
        }
        else {
            return obj->e + clr * (radiance(refL, depth, seed) * Re + radiance(Line3(x, d_fra), depth, seed)) * Tr; 
        }
    }
    return Vec3();
}
void Canvas::render(int samples, int w, int h, double dis, double ratio) {
    Vec3 cx(w *ratio / h, 0, 0), cy = cx.det(this->camera.d).normal() * ratio; 
    Vec3 *c = new Vec3[h * w], r;
#pragma omp parallel for schedule(dynamic, 1) private(r)       // OpenMP
    for(int y = 0; y < h; ++y) {
        // fprintf(stderr, "\rRendering (%d spp) %.5f", samples * 4, 100.0 * y / (h - 1));
        fprintf(stderr,"\rRendering (%d spp) %5.2f%%",samples*4,100.* y/(h-1));
        // printf("Rendering (%d spp) %.5f", samples * 4, 100.0 * y / (h - 1));
        for(int x = 0; x < w; ++x) {
            unsigned short seedX[3] = {y, y * y, y * y * y};
            int idx = (h - 1 - y) * w + x;
            for(int sx = 0; sx < 2; ++ sx) {
                for(int sy = 0; sy < 2; ++sy, r=Vec3()) {
                    // Vec3 r(0, 0, 0);
                    for(int t = 0; t < samples; ++ t) {
                        double r1 = 2 * rnd::erand48(seedX);
                        double dx = (r1 < 1 ? sqrt(r1) - 1 : 1 - sqrt(2 - r1)); 
                        double r2 = 2 * rnd::erand48(seedX);
                        double dy = (r2 < 1 ? sqrt(r2) - 1 : 1 - sqrt(2 - r2));
                        Vec3 dir = cx * (((sx + 0.5 + dx) / 2 + x) / w - 0.5) + 
                                 cy * (((sy + 0.5 + dy) / 2 + y) / h - 0.5) +
                                 this->camera.d;
                        r = r + radiance(Line3(this->camera.o + dir * dis, dir.normal()), 0, seedX);
                    }
                    r = r * (1.0 / samples);
                    c[idx] = c[idx] + Vec3(clamp(r.x), clamp(r.y), clamp(r.z)) * 0.25;
                }
            }
            // c[idx] = c[idx] * 0.25;
        }
    }
    FILE* f = fopen(path, "w");
    fprintf(f, "P3\n%d %d\n%d\n", w, h, 255);
    for (int i = 0; i < w * h; i++) {
        fprintf(f,"%d %d %d ", toInt(c[i].x), toInt(c[i].y), toInt(c[i].z));
    }
}