#include<iostream>
#include"vec3.h"
using namespace std;

int main(){
    vec3 point1, point2, point3, point4;
    point1.x = 1;
    point1.y = 3;
    point1.z = -5;

    point2 = vec3(4, -2, -1);

    point3 = point1 + point2;
    cout << point3.x << " " << point3.y << " " << point3.z <<endl;

    point3 = point1 - point2;
    cout << point3.x << " " << point3.y << " " << point3.z <<endl;

    point3 = point1 * 10;
    cout << point3.x << " " << point3.y << " " << point3.z <<endl;

    point3 = point1 / 10;
    cout << point3.x << " " << point3.y << " " << point3.z <<endl;

    cout << vec3::dot(point1, point2) <<endl;

    point3 = vec3::cross(point1, point2);
    cout << point3.x << " " << point3.y << " " << point3.z <<endl;

    cout << point1.length() <<endl;

    point3 = point1.unit();
    cout << point3.x << " " << point3.y << " " << point3.z <<endl;

    return 0;
}
