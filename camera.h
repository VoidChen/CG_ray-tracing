#include"obj.h"

class camera{
    public:
        vec3 origin;
        int width;
        int height;
        vec3 lowerleft;
        vec3 horizontal;
        vec3 vertical;
        ray** primary;
        vec3** color;

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
            color = new vec3*[height];
            for(int i = 0; i < height; ++i){
                primary[i] = new ray[width];
                color[i] = new vec3[width];
                for(int j = 0; j < width; ++j){
                    primary[i][j] = ray(origin, (lowerleft + unit_h * (j+0.5) + unit_v * (i+0.5) - origin));
                    color[i][j] = vec3(0, 0, 0);
                }
            }
        }
};
