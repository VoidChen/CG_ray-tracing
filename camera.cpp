#include<iostream>
#include"obj.h"
using namespace std;

class camera{
    public:
        vec3 origin;
        int width;
        int height;
        vec3 lowerleft;
        vec3 horizontal;
        vec3 vertical;
        ray** primary;

        camera(){
        }

        camera(vec3 origin, int width, int height, vec3 ll, vec3 h, vec3 v){
            //init camera
            this->origin = origin;
            this->width = width;
            this->height = height;
            lowerleft = ll;
            horizontal = h;
            vertical = v;

            //primary rays
            vec3 unit_h = horizontal / width;
            vec3 unit_v = vertical / height;

            primary = new ray*[height];
            for(int i = 0; i < height; ++i){
                primary[i] = new ray[width];
                for(int j = 0; j < width; ++j)
                    primary[i][j] = ray(origin, (lowerleft + unit_h * (j+0.5) + unit_v * (i+0.5) - origin));
            }
        }
};

void print_vec3(vec3 v){
    cout << "(" << v.x << ", " << v.y << ", " << v.z << ")"<<endl;
}

int main(){
    camera C;

    C = camera(vec3(0, 0, 0), 200, 100, vec3(-2, -1, -1), vec3(4, 0, 0), vec3(0, 2, 0));
    for(int i = 0; i < C.height; ++i){
        for(int j = 0; j < C.width; ++j)
            print_vec3(C.primary[i][j].direction);
    }

    C = camera(vec3(0, 0, 0), 5, 3, vec3(-2, -1, -1), vec3(4, 0, 0), vec3(0, 2, 0));
    for(int i = 0; i < C.height; ++i){
        for(int j = 0; j < C.width; ++j)
            print_vec3(C.primary[i][j].direction);
    }

    return 0;
}
