#include<vector>
#include"camera.h"

//ray-object hit test
int multi_hit(ray r, vector<obj*> objs){
    int result = -1;
    double t, t_min;
    for(unsigned int i = 0; i < objs.size(); ++i){
        t = objs[i]->hit(r);
        if(t != -1 && (t < t_min || result == -1)){
            result = i;
            t_min = t;
        }
    }
    return result;
}

int main(){
    //init scene
    vector<obj*> objs;
    camera C;
    vec3 light;

    objs.push_back(new sphere(vec3(6, 10, -40), 6));
    objs.push_back(new sphere(vec3(-6, -3, -35), 6));
    objs.push_back(new plane(vec3(0, -25, 0), vec3(0, 1, 0)));

    C = camera(vec3(0, 0, 0), 1200, 600, vec3(-2, -0.8, -1), vec3(4, 0, 0), vec3(0, 2, 0));
    light = vec3(-15, 20, -15);

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
                    C.color[i][j] = vec3(255, 255, 255) * diffuse;
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
    image = ppm(C.width, C.height);
    image.set_color(C.color);
    image.output("output.ppm");

    return 0;
}
