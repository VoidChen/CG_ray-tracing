#include<iostream>
#include"vec3.h"
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

int main(){
    ray r1, r2;
    vec3 p1, p2;

    r1 = ray(1, 3, -5, 4, -2, -1);
    r2 = ray(vec3(1, 3, -5), vec3(4, -2, -1));

    p1 = r1.point(1.5);
    p2 = r2.point(3.14);

    cout << p1.x << " " << p1.y << " " << p1.z <<endl;
    cout << p2.x << " " << p2.y << " " << p2.z <<endl;

    sphere s1;
    s1 = sphere(vec3(1, 2, 3), 10);

    return 0;
}
