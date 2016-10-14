#include"camera.h"

int main(){
    //init scene
    camera C;
    sphere S;
    vec3 light;

    C = camera(vec3(0, 0, 0), 1200, 600, vec3(-2, -1, -1), vec3(4, 0, 0), vec3(0, 2, 0));
    S = sphere(vec3(1, 2, -15), 5);
    light = vec3(-10, 15, -2);

    //render
    double t, diffuse;
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

    //generate ppm
    ppm image;
    image = ppm(C.width, C.height);
    image.set_color(C.color);
    image.output("output.ppm");

    return 0;
}
