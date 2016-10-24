#include<cstddef>
#include"obj.h"

class camera{
    public:
        vec3 origin;
        int width;
        int height;
        int sample;
        vec3 lowerleft;
        vec3 horizontal;
        vec3 vertical;
        ray** primary;
        vec3** color;

        camera(vec3 origin, int width, int height, int sample, vec3 ll, vec3 h, vec3 v){
            this->origin = origin;
            this->width = width * sample;
            this->height = height * sample;
            this->sample = sample;
            lowerleft = ll;
            horizontal = h;
            vertical = v;
            init_primary_rays();
        }

        ~camera(){
            for(int i = 0; i < height; ++i){
                delete [] primary[i];
                delete [] color[i];
            }
            delete [] primary;
            delete [] color;
        }

    private:
        void init_primary_rays(){
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
