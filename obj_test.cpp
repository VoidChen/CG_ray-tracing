#include<iostream>
#include"obj.h"
using namespace std;

void print_vec3(vec3 v){
    cout << "(" << v.x << ", " << v.y << ", " << v.z << ")"<<endl;
}

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

    //sphere hit test
    double t1;
    //1 hit
    r1 = ray(vec3(0, 0, 0), vec3(1, 1, 0));
    s1 = sphere(vec3(1, 1, -1), 1);
    t1 = s1.hit(r1);
    cout << t1 << endl;
    print_vec3(r1.point(t1));

    //1 hit
    r1 = ray(vec3(0, 0, 0), vec3(1, 1, 0));
    s1 = sphere(vec3(0, 0, 0), 1);
    t1 = s1.hit(r1);
    cout << t1 << endl;
    print_vec3(r1.point(t1));

    //no hit
    r1 = ray(vec3(0, 0, 0), vec3(1, 1, 0));
    s1 = sphere(vec3(1, 1, -1), 0.9);
    t1 = s1.hit(r1);
    cout << t1 << endl;
    print_vec3(r1.point(t1));

    //2 hit
    r1 = ray(vec3(0, 0, 0), vec3(1, 1, 0));
    s1 = sphere(vec3(1, 1, -1), 1.7);
    t1 = s1.hit(r1);
    cout << t1 << endl;
    print_vec3(r1.point(t1));

    return 0;
}
