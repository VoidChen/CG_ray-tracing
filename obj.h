#include<vector>
#ifndef vec3_h
#include"vec3.h"
#define vec3_h
#endif
using namespace std;

class ray{
    public:
        vec3 origin;
        vec3 direction;

        ray(){
        }

        ray(double ox, double oy, double oz, double dx, double dy, double dz){
            origin = vec3(ox, oy, oz);
            direction = vec3(dx, dy, dz);
        }

        ray(vec3 origin, vec3 direction){
            this->origin = origin;
            this->direction = direction;
        }

        vec3 point(double t){
            return origin + (direction * t);
        }

        ray reflect(vec3 normal){
            ray result;
            result.origin = this->origin;
            result.direction = normal.unit()*vec3::dot(normal.unit(), this->direction.unit())*2 - this->direction.unit();
            return result;
        }

        ray refract(vec3 hit_point, vec3 normal, double ri1, double ri2){
            ray result;
            double ri = ri1 / ri2;
            double c = vec3::dot(this->direction.unit(), normal) * -1;
            result.origin = hit_point;
            result.direction = (this->direction * ri) + (normal * (ri*c - sqrt(1 - ri*ri*(1-c*c))));
            return result;
        }
};

class light{
    public:
        vec3 origin;
        vec3 intensity;

        light(vec3 origin, vec3 intensity){
            this->origin = origin;
            this->intensity = intensity;
        }
};

class obj{
    protected:
        vec3 surface_color;
    public:
        double ri;

        obj(){
        }

        vec3 color(vec3 light){
            vec3 result;
            result.r = light.r * surface_color.r;
            result.g = light.g * surface_color.g;
            result.b = light.b * surface_color.b;

            return result;
        }

        virtual double hit(ray &r) = 0;
        virtual vec3 normal(vec3 &hit_point) = 0;
};

class sphere: public obj{
    public:
        vec3 center;
        double radius;

        sphere(){
        }

        sphere(vec3 center, double radius, vec3 color, double ri = 0){
            this->center = center;
            this->radius = radius;
            this->surface_color = color;
            this->ri = ri;
        }

        double hit(ray &r) override{
            double a = vec3::dot(r.direction, r.direction);
            double b = vec3::dot(r.direction * 2, r.origin - center);
            double c = vec3::dot(r.origin - center, r.origin - center) - radius * radius;

            if(b*b - 4*a*c < 0)
                return -1;
            else{
                double t1 = (-1*b + sqrt(b*b - 4*a*c)) / (2*a);
                double t2 = (-1*b - sqrt(b*b - 4*a*c)) / (2*a);
                if(t1 < 1.0e-10)
                    return -1;
                else{
                    if(t2 < 1.0e-10)
                        return t1;
                    else
                        return t2;
                }
            }
        }

        vec3 normal(vec3 &hit_point) override{
            return hit_point - center;
        }
};

class plane: public obj{
    public:
        vec3 point;
        vec3 plane_normal;

        plane(){
        }

        plane(vec3 point, vec3 plane_normal, vec3 color, double ri = 0){
            this->point = point;
            this->plane_normal = plane_normal;
            this->surface_color = color;
            this->ri = ri;
        }

        double hit(ray &r) override{
            double a = vec3::dot(r.direction, plane_normal);
            double b = vec3::dot(point - r.origin, plane_normal);

            if(a == 0)
                return -1;
            else
                return b/a >= -1.0e-10 ? b/a: -1;
        }

        vec3 normal(vec3 &hit_point) override{
            return plane_normal;
        }
};

//ray-object hit test
int multi_hit(ray &r, vector<obj*> &objs){
    int result = -1;
    double t, t_min;
    for(unsigned int i = 0; i < objs.size(); ++i){
        t = objs[i]->hit(r);
        if(t != -1 && t > 1.0e-10 && (t < t_min || result == -1)){
            result = i;
            t_min = t;
        }
    }
    return result;
}
