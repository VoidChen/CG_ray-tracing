#include<vector>
#include"camera.h"
#include"ppm.h"
#include"bmp.h"
using namespace std;

int main(){
    //init
    camera C = camera(vec3(0, 0, 0), 1500, 900, 3, vec3(-2.5, -1.6, -2.25), vec3(5, 0, 0), vec3(0, 3, 0));
    light L = light(vec3(-15, 25, -10), vec3(255, 255, 255));

    vector<obj*> objs;
    objs.push_back(new sphere(vec3(7, 2.5, -35), 1.5, vec3(1.0, 0.6, 0.6), vec3(1, 0, 0), 0)); //pink
    objs.push_back(new sphere(vec3(10, 0.5, -32.5), 1.5, vec3(0.2, 0.9, 0.9), vec3(1, 0, 0), 0)); //light blue
    objs.push_back(new sphere(vec3(4.5, -1, -27.5), 1.5, vec3(0.7, 0.45, 0.9), vec3(1, 0, 0), 0)); //purple
    objs.push_back(new sphere(vec3(-5, 16, -55), 1.5, vec3(1.0, 0.1, 0.1), vec3(1, 0, 0), 0)); //red
    objs.push_back(new sphere(vec3(-12, 5.5, -37.5), 1.5, vec3(0.2, 0.5, 1), vec3(1, 0, 0), 0)); //dark blue
    objs.push_back(new sphere(vec3(-7, 9, -40), 4, vec3(1.0, 1.0, 0.35), vec3(0.75, 0.25, 0), 0)); //yellow
    objs.push_back(new sphere(vec3(-6, -6, -27.5), 1, vec3(0.9, 0.9, 0.9), vec3(1, 0, 0), 0)); //gray
    objs.push_back(new sphere(vec3(-4, -1, -30), 4, vec3(0, 0, 0), vec3(0, 0, 1.0), 1.8, vec3(0.95, 0.95, 0.95))); //big glass
    objs.push_back(new sphere(vec3(13, -2, -47.5), 1.5, vec3(0, 0, 0), vec3(0, 0, 1.0), 1.8, vec3(0.95, 0.95, 0.95))); //small glass
    objs.push_back(new sphere(vec3(5, 10, -50), 7, vec3(0, 0, 0), vec3(0, 1.0, 0), 0)); //mirror
    objs.push_back(new plane(vec3(0, -25, 0), vec3(0, 1, 0), vec3(0.3, 0.9, 0.3), vec3(1, 0, 0), 0)); //ground

    //render
    C.render(objs, L, 15);

    //generate image
    PPM ppm = PPM(C.width, C.height, C.ca->color);
    ppm.output("output.ppm");

    BMP bmp = BMP(C.width, C.height, C.ca->color);
    bmp.output("output.bmp");

    return 0;
}
