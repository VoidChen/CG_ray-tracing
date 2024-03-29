#include<vector>
#ifndef obj_h
#include"obj.h"
#define obj_h
#endif
using namespace std;

//ray-object hit test
int multi_hit(ray &r, vector<obj*> &objs){
    int result = -1;
    double t, t_min = 0;
    for(unsigned int i = 0; i < objs.size(); ++i){
        t = objs[i]->hit(r);
        if(t != -1 && t > 1.0e-10 && (t < t_min || result == -1)){
            result = i;
            t_min = t;
        }
    }
    return result;
}

vec3 background_color(ray &r){
    return vec3((1 - (r.direction.unit().y + 1)/2) * 255, 255, 255);
}

vec3 attenuation(ray &r, vector<obj*> &objs, light &l, bool flag){
    int closest = multi_hit(r, objs);
    if(closest == -1)
        return l.intensity;
    else{
        obj* hit_obj = objs[closest];
        if(hit_obj->ri != 0){
            vec3 hit_point = r.point(hit_obj->hit(r));
            ray next_ray = ray(hit_point, r.direction);
            vec3 input_light = attenuation(next_ray, objs, l, !flag);
            if(flag)
                //light pass obj
                return hit_obj->attenuation(input_light, (hit_point - r.origin).length());
            else
                //light pass air
                return input_light;
        }
        else
            return vec3(0, 0, 0);
    }
}

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
            vec3 local_light = attenuation(shadow_ray, objs, l, false);
            diffuse = vec3::dot(normal, shadow_ray.direction.unit());
            result += hit_obj->color(local_light) * diffuse * hit_obj->local_fix;

            if(n > 0){
                //reflect
                ray reflect_ray = ray(hit_point, r.origin - hit_point).reflect(normal);
                vec3 reflect_color = trace(reflect_ray, objs, l, n-1);
                if(reflect_color != vec3(-1, -1, -1)){
                    diffuse = vec3::dot(normal, reflect_ray.direction.unit());
                    if(diffuse < 0)
                        diffuse *= -1;
                    result += reflect_color * diffuse * hit_obj->reflect_fix;
                }

                //refract
                if(hit_obj->ri != 0){
                    ray refract_ray;
                    if(vec3::dot(normal, r.direction) < 0)
                        refract_ray = r.refract(hit_point, normal, 1.0, hit_obj->ri);
                    else
                        refract_ray = r.refract(hit_point, normal * -1, hit_obj->ri, 1.0);
                    if(refract_ray.direction != vec3(0, 0, 0)){
                        vec3 refract_color = trace(refract_ray, objs, l, n-1);
                        if(refract_color != vec3(-1, -1, -1)){
                            diffuse = vec3::dot(normal, refract_ray.direction.unit());
                            if(diffuse < 0)
                                diffuse *= -1;
                            result += refract_color * diffuse * hit_obj->refract_fix;
                        }
                    }
                }
            }

            return result;
        }
        else
            return background_color(r);
    }
}
