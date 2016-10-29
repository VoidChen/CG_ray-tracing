#include<vector>
#include"camera.h"
#include"tracer.h"
#include"ppm.h"
using namespace std;

int main(){
    //init
    camera C = camera(vec3(0, 0, 0), 1500, 900, 3, vec3(-2.5, -1.3, -1.5), vec3(5, 0, 0), vec3(0, 3, 0));
    light L = light(vec3(-15, 25, -15), vec3(255, 255, 255));

    vector<obj*> objs;
    objs.push_back(new sphere(vec3(7, 2.5, -35), 1.5, vec3(1.0, 0.6, 0.6), vec3(1, 0, 0), 0)); //pink
    objs.push_back(new sphere(vec3(10, 0.5, -32.5), 1.5, vec3(0.2, 0.9, 0.9), vec3(1, 0, 0), 0)); //light blue
    objs.push_back(new sphere(vec3(4.5, -1, -27.5), 1.5, vec3(0.7, 0.45, 0.9), vec3(1, 0, 0), 0)); //purple
    objs.push_back(new sphere(vec3(-5, 16, -55), 1.5, vec3(1.0, 0.1, 0.1), vec3(1, 0, 0), 0)); //red
    objs.push_back(new sphere(vec3(-12, 5.5, -37.5), 1.5, vec3(0.2, 0.5, 1), vec3(1, 0, 0), 0)); //dark blue
    objs.push_back(new sphere(vec3(-7, 9, -40), 4, vec3(1.0, 1.0, 0.35), vec3(0.75, 0.25, 0), 0)); //yellow
    objs.push_back(new sphere(vec3(-7, -6, -25), 1, vec3(0.9, 0.9, 0.9), vec3(1, 0, 0), 0)); //gray
    objs.push_back(new sphere(vec3(-8, -4, -35), 7.5, vec3(0, 0, 0), vec3(0, 0.5, 1.0), 1.2)); //glass
    objs.push_back(new sphere(vec3(5, 10, -50), 7, vec3(0, 0, 0), vec3(0, 1.0, 0), 0)); //mirror
    objs.push_back(new plane(vec3(0, -25, 0), vec3(0, 1, 0), vec3(0.3, 0.9, 0.3), vec3(0.9, 0.6, 0))); //ground

    //render
    vec3 trace_color;
    for(int i = 0; i < C.height; ++i){
        for(int j = 0; j < C.width; ++j){
            trace_color = trace(C.primary[i][j], objs, L, 15);
            if(trace_color != vec3(-1, -1, -1))
                C.color[i][j] = trace_color;
            else
                C.color[i][j] = vec3(255*(C.height-i)/C.height, 255, 255);
        }
    }

    //generate ppm
    ppm image = ppm(C.width/C.sample, C.height/C.sample);
    image.set_color(C.color, C.sample);
    image.output("output.ppm");

    return 0;
}
