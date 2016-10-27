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

            //direct
            ray shadow_ray = ray(hit_point, l.origin - hit_point);
            if(multi_hit(shadow_ray, objs) == -1){
                diffuse = vec3::dot(normal, shadow_ray.direction.unit());
                result = result + hit_obj->color(l.intensity) * diffuse;
            }

            if(n > 0){
                //reflect
                ray reflect_ray = ray(hit_point, r.origin - hit_point).reflect(normal);
                vec3 reflect_color = trace(reflect_ray, objs, l, n-1);
                if(reflect_color != vec3(-1, -1, -1)){
                    diffuse = vec3::dot(normal, reflect_ray.direction.unit());
                    if(diffuse < 0)
                        diffuse = diffuse * -1;
                    result = result + reflect_color * diffuse * 0.5;
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
                        result = result + refract_color * diffuse * 1;
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
    camera C = camera(vec3(0, 0, 0), 1200, 600, 3, vec3(-2, -0.75, -1), vec3(4, 0, 0), vec3(0, 2, 0));
    light L = light(vec3(-15, 20, -15), vec3(255, 255, 255));

    vector<obj*> objs;
    objs.push_back(new sphere(vec3(6, 10, -40), 6, vec3(1.0, 1.0, 0.35), 0));
    objs.push_back(new sphere(vec3(-6, -3, -35), 6, vec3(0, 0, 0), 1));
    objs.push_back(new plane(vec3(0, -25, 0), vec3(0, 1, 0), vec3(0.3, 0.9, 0.3)));

    //render
    vec3 trace_color;
    for(int i = 0; i < C.height; ++i){
        for(int j = 0; j < C.width; ++j){
            trace_color = trace(C.primary[i][j], objs, L, 10);
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
