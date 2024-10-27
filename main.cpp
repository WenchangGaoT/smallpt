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
}
