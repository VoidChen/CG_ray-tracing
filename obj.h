#include"vec3.h"

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

class sphere{
    public:
        vec3 center;
        double radius;

        sphere(){
        }

        sphere(vec3 center, double radius){
            this->center = center;
            this->radius = radius;
        }

};
