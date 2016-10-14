#include<iostream>
#include"obj.h"
#include"ppm.h"
using namespace std;

class camera{
    public:
        vec3 origin;
        int width;
        int height;
        vec3 lowerleft;
        vec3 horizontal;
        vec3 vertical;
        ray** primary;
        vec3** color;

        camera(){
        }

        camera(vec3 origin, int width, int height, vec3 ll, vec3 h, vec3 v){
            //init camera
            this->origin = origin;
            this->width = width;
            this->height = height;
            lowerleft = ll;
            horizontal = h;
            vertical = v;

            //primary rays
            vec3 unit_h = horizontal / width;
            vec3 unit_v = vertical / height;

            primary = new ray*[height];
            color = new vec3*[height];
            for(int i = 0; i < height; ++i){
                primary[i] = new ray[width];
                color[i] = new vec3[width];
                for(int j = 0; j < width; ++j){
                    primary[i][j] = ray(origin, (lowerleft + unit_h * (j+0.5) + unit_v * (i+0.5) - origin));
                    color[i][j] = vec3(255*(height-i)/height, 255, 255);
                }
            }
        }
};

void print_vec3(vec3 v){
    cout << "(" << v.x << ", " << v.y << ", " << v.z << ")"<<endl;
}

int main(){
    camera C;
    sphere S;
    vec3 light;
    double t, diffuse;

    C = camera(vec3(0, 0, 0), 1200, 600, vec3(-2, -1, -1), vec3(4, 0, 0), vec3(0, 2, 0));
    S = sphere(vec3(1, 2, -15), 5);
    light = vec3(-10, 15, -2);
    for(int i = 0; i < C.height; ++i){
        for(int j = 0; j < C.width; ++j){
            t = S.hit(C.primary[i][j]);
            if(t != -1){
                vec3 hit_point = C.primary[i][j].point(t);
                diffuse = vec3::dot((hit_point - S.center).unit(), (light - hit_point).unit());
                C.color[i][j] = vec3(255, 255, 255) * diffuse;
            }
        }
    }

    ppm image;

    image = ppm(C.width, C.height);
    image.set_color(C.color);
    image.output("output.ppm");

    return 0;
}
