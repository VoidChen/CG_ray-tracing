#include<vector>
#include"camera.h"
#include"ppm.h"
using namespace std;

vec3 trace(ray r, vector<obj*> &objs, vec3 light, int n){
    if(n < 0)
        return vec3(0, 0, 0);
    else{
        int closest;
        double diffuse;
        closest = multi_hit(r, objs);
        if(closest != -1){
            vec3 result = vec3(0, 0, 0);
            vec3 hit_point = r.point(objs[closest]->hit(r));

            //direct
            if(multi_hit(ray(hit_point, light - hit_point), objs) == -1){
                diffuse = vec3::dot(objs[closest]->normal(hit_point).unit(), (light - hit_point).unit());
                result = result + objs[closest]->reflect(vec3(255, 255, 255)) * diffuse;
            }

            //reflect
            if(n > 0){
                ray reflect_ray = ray(hit_point, r.origin - hit_point).reflect(objs[closest]->normal(hit_point));
                vec3 reflect_color = trace(reflect_ray, objs, light, n-1);
                if(reflect_color != vec3(-1, -1, -1)){
                    diffuse = vec3::dot(objs[closest]->normal(hit_point).unit(), reflect_ray.direction.unit());
                    result = result + reflect_color * diffuse * 0.3;
                }
            }

            return result;
        }
        else
            return vec3(-1, -1, -1);
    }
}

int main(){
    //init
    camera C = camera(vec3(0, 0, 0), 1200, 600, 3, vec3(-2, -0.75, -1), vec3(4, 0, 0), vec3(0, 2, 0));
    vec3 light = vec3(-15, 20, -15);

    vector<obj*> objs;
    objs.push_back(new sphere(vec3(6, 10, -40), 6, vec3(1.0, 1.0, 0.35)));
    objs.push_back(new sphere(vec3(-6, -3, -35), 6, vec3(1.0, 0.6, 0.6)));
    objs.push_back(new plane(vec3(0, -25, 0), vec3(0, 1, 0), vec3(0.3, 0.9, 0.3)));

    //render
    vec3 trace_color;
    for(int i = 0; i < C.height; ++i){
        for(int j = 0; j < C.width; ++j){
            trace_color = trace(C.primary[i][j], objs, light, 10);
            if(trace_color != vec3(-1, -1, -1))
                C.color[i][j] = trace_color;
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
