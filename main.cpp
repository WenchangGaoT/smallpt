#include <cstdlib>
#include <cstring>
#include "./include/object.h"
#include "./include/_random.h"
#include "./include/_const.hpp"
#include "./include/canvas.h"

Sphere spheres[] = {
        Sphere(600, Vec3(50,681.6-.27,81.6),Vec3(12,10,9),  Vec3(), DIFF),
        Sphere(1e5, Vec3( 1e5+1,40.8,81.6), Vec3(),Vec3(.55,.45,.75),DIFF),//Left
        Sphere(1e5, Vec3(-1e5+99,40.8,81.6),Vec3(),Vec3(.35,.75,.25),DIFF),//Rght
        Sphere(1e5, Vec3(50,40.8, 1e5),     Vec3(),Vec3(.45,.35,.35),DIFF),//Back
        Sphere(1e5, Vec3(50,40.8,-1e5+170), Vec3(),Vec3(),           DIFF),//Frnt
        Sphere(1e5, Vec3(50, 1e5, 81.6),    Vec3(),Vec3(.75,.75,.75),DIFF),//Botm
        Sphere(1e5, Vec3(50,-1e5+81.6,81.6),Vec3(),Vec3(.75,.75,.75),DIFF),//Top
        Sphere(16.5,Vec3(27,16.5,47),       Vec3(),Vec3(1,1,1) * .99, SPEC),
        Sphere(16.5,Vec3(73,16.5,78),       Vec3(),Vec3(.95,.99,1) * .98, REFR),
        Sphere(7 ,Vec3(50,25,78),       Vec3(),Vec3(1,0,1) * .70, REFR),
        Sphere(7 ,Vec3(50,7,78),       Vec3(),Vec3(.6,0,1) * .50, REFR),
        Sphere(25 ,Vec3(20,25,80),       Vec3(),Vec3(.6,.8,1) * .95, SPEC),
        Sphere(600, Vec3(50,-651.6-.27,81.6),Vec3(12,12,12),  Vec3(), DIFF)
};

//Canvas(int _n, Sphere* _objects, Line3 _camera, char* _path);
//render(int samples, int w, int h, double dis, double ratio)

int main(int argc, char *argv[]) {
    Line3 camera = Line3(Vec3(50,52,295.6), Vec3(0,-0.042612,-1).normal());
    int w = 1024, h = 768, samps = (argc == 2 ? atoi(argv[1]) / 4 : 1);
    double d = 140;
    char path[] = "image.ppm";
    Canvas can(13, spheres, camera, path);
    can.render(samps, w, h, d, 0.5135);


//     int w=1024, h=768, samps = (argc == 2 ? atoi(argv[1]) / 4 : 1);
//     Line3 cam(Vec3(50,52,295.6), Vec3(0,-0.042612,-1).normal()); // cam pos, dir
//     char path[] = "image.ppm";
//     Canvas can(8, spheres, cam, path);
//     Vec3 cx=Vec3(w*.5135 / h), cy=((cx.det(can.camera.d)).normal())*.5135, r, *c=new Vec3[w * h];
//     Line3  rr;
    
// #pragma omp parallel for schedule(dynamic, 1) private(r)       // OpenMP
//     for (unsigned short y = 0; y < h; y++){                       // Loop over image rows
//         unsigned short oo = y * y * y, Xi[3] = {0, 0, oo};
//         fprintf(stderr,"\rRendering (%d spp) %5.2f%%", samps * 4, 100.* y/(h-1));
//         for (unsigned short x = 0; x < w; x++)   // Loop cols
//             for (int sy = 0, i = (h-y-1) * w + x; sy < 2; sy++)     // 2x2 subpixel rows
//                 for (int sx = 0; sx < 2; sx++, r = Vec3()){        // 2x2 subpixel cols
//                     for (int s = 0; s < samps; s++){
//                         double r1 = 2 * rnd::erand48(Xi), dx = r1<1 ? sqrt(r1) - 1 : 1 - sqrt(2 - r1);
//                         double r2 = 2 * rnd::erand48(Xi), dy = r2<1 ? sqrt(r2) - 1 : 1 - sqrt(2 - r2);
//                         // double r1 = 2 * rnd::erand48(Xi), dx = r1 - 1;
//                         // double r2 = 2 * rnd::erand48(Xi), dy = r2 - 1;
//                         Vec3 d = cx*( ( (sx+.5 + dx)/2 + x) / w - .5) +
//                                 cy*( ( (sy+.5 + dy)/2 + y) / h - .5) + cam.d;
//                         r = r + can.radiance(Line3(cam.o+d * 140,d.normal()),0,Xi)*(1./samps);
//                     } // Camera rays are pushed ^^^^^ forward to start in interior
//                     c[i] = c[i] + Vec3(clamp(r.x),clamp(r.y),clamp(r.z)) *.25;
//                 }
//     }
//     FILE *f = fopen("image.ppm", "w");         // Write image to PPM file.
//     fprintf(f, "P3\n%d %d\n%d\n", w, h, 255);
//     for (int i=0; i<w*h; i++)
//         fprintf(f,"%d %d %d ", toInt(c[i].x), toInt(c[i].y), toInt(c[i].z));
}