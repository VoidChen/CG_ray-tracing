#include<vector>
#include"camera.h"
#include"ppm.h"
using namespace std;

vec3 trace(ray &r, vector<obj*> &objs, light &l, int n){
    if(n < 0)
        return vec3(0, 0, 0);
    else{
        int closest = multi_hit(r, objs);
        if(closest != -1){
            obj* hit_obj = objs[closest];
            vec3 hit_point = r.point(hit_obj->hit(r));
            vec3 normal = hit_obj->normal(hit_point).unit();
            vec3 result = vec3(0, 0, 0);
            double diffuse;

            //local
            ray shadow_ray = ray(hit_point, l.origin - hit_point);
            if(multi_hit(shadow_ray, objs) == -1){
                diffuse = vec3::dot(normal, shadow_ray.direction.unit());
                result = result + hit_obj->color(l.intensity) * diffuse * hit_obj->local_fix;
            }

            if(n > 0){
                //reflect
                ray reflect_ray = ray(hit_point, r.origin - hit_point).reflect(normal);
                vec3 reflect_color = trace(reflect_ray, objs, l, n-1);
                if(reflect_color != vec3(-1, -1, -1)){
                    diffuse = vec3::dot(normal, reflect_ray.direction.unit());
                    if(diffuse < 0)
                        diffuse = diffuse * -1;
                    result = result + reflect_color * diffuse * hit_obj->reflect_fix;
                }

                //refract
                if(hit_obj->ri != 0){
                    ray refract_ray;
                    if(vec3::dot(normal, r.direction) < 0)
                        refract_ray = r.refract(hit_point, normal, 1.0, hit_obj->ri);
                    else
                        refract_ray = r.refract(hit_point, normal * -1, hit_obj->ri, 1.0);
                    vec3 refract_color = trace(refract_ray, objs, l, n-1);
                    if(refract_color != vec3(-1, -1, -1)){
                        diffuse = vec3::dot(normal, refract_ray.direction.unit());
                        if(diffuse < 0)
                            diffuse = diffuse * -1;
                        result = result + refract_color * diffuse * hit_obj->refract_fix;
                    }
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
    objs.push_back(new sphere(vec3(-8, -4, -35), 7.5, vec3(0, 0, 0), vec3(0, 0.5, 1.0), 1)); //glass
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
