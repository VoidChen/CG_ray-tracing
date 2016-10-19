#include<vector>
#include"camera.h"
#include"ppm.h"
using namespace std;

int main(){
    //init
    camera C = camera(vec3(0, 0, 0), 1200, 600, 3, vec3(-2, -0.75, -1), vec3(4, 0, 0), vec3(0, 2, 0));
    vec3 light = vec3(-15, 20, -15);

    vector<obj*> objs;
    objs.push_back(new sphere(vec3(6, 10, -40), 6, vec3(1.0, 1.0, 0.35)));
    objs.push_back(new sphere(vec3(-6, -3, -35), 6, vec3(1.0, 0.6, 0.6)));
    objs.push_back(new plane(vec3(0, -25, 0), vec3(0, 1, 0), vec3(0.3, 0.9, 0.3)));

    //render
    int closest;
    double diffuse;
    vec3 hit_point;
    for(int i = 0; i < C.height; ++i){
        for(int j = 0; j < C.width; ++j){
            closest = multi_hit(C.primary[i][j], objs);
            if(closest != -1){
                hit_point = C.primary[i][j].point(objs[closest]->hit(C.primary[i][j]));
                if(multi_hit(ray(light, hit_point - light), objs) == closest){
                    diffuse = vec3::dot(objs[closest]->normal(hit_point).unit(), (light - hit_point).unit());
                    C.color[i][j] = objs[closest]->reflect(vec3(255, 255, 255)) * diffuse;
                }
                else
                    C.color[i][j] = vec3(0, 0, 0);
            }
            else
                C.color[i][j] = vec3(255*(C.height-i)/C.height, 255, 255);
        }
    }

    //generate ppm
    ppm image;
    image = ppm(C.width/C.sample, C.height/C.sample);
    image.set_color(C.color, C.sample);
    image.output("output.ppm");

    return 0;
}
