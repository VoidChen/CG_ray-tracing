#ifndef vec3_h
#include"vec3.h"
#define vec3_h
#endif

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
};

class obj{
    public:
        obj(){
        }

        virtual double hit(ray r) = 0;
        virtual vec3 normal(vec3 point) = 0;
};

class sphere: public obj{
    public:
        vec3 center;
        double radius;

        sphere(){
        }

        sphere(vec3 center, double radius){
            this->center = center;
            this->radius = radius;
        }

        double hit(ray r){
            double a = vec3::dot(r.direction, r.direction);
            double b = vec3::dot(r.direction * 2, r.origin - center);
            double c = vec3::dot(r.origin - center, r.origin - center) - radius * radius;

            if(b*b - 4*a*c < 0)
                return -1;
            else{
                double t1 = (-1*b + sqrt(b*b - 4*a*c)) / (2*a);
                double t2 = (-1*b - sqrt(b*b - 4*a*c)) / (2*a);
                if(t1 < 0)
                    return -1;
                else{
                    if(t2 < 0)
                        return t1;
                    else
                        return t2;
                }
            }
        }

        virtual vec3 normal(vec3 point){
            return point - center;
        }
};
