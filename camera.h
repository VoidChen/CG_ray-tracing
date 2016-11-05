#include<cstddef>
#include"tracer.h"
#ifndef obj_h
#include"obj.h"
#define obj_h
#endif

class color_array{
    public:
        int width;
        int height;
        vec3** color;

        color_array(int width, int height){
            this->width = width;
            this->height = height;
            color = new vec3*[height];
            for(int i = 0; i < height; ++i)
                color[i] = new vec3[width];
        }

        ~color_array(){
            for(int i = 0; i < height; ++i)
                delete [] color[i];
            delete [] color;
        }
};

class camera{
    public:
        vec3 origin;
        int width;
        int height;
        int width_s;
        int height_s;
        int sample;
        vec3 lowerleft;
        vec3 horizontal;
        vec3 vertical;
        ray** primary;
        color_array* raw;
        color_array* avg;

        camera(vec3 origin, int width, int height, int sample, vec3 ll, vec3 h, vec3 v){
            this->origin = origin;
            this->width = width;
            this->height = height;
            this->width_s = width * sample;
            this->height_s = height * sample;
            this->sample = sample;
            lowerleft = ll;
            horizontal = h;
            vertical = v;
            init_primary_rays();
            raw = new color_array(width_s, height_s);
        }

        ~camera(){
            for(int i = 0; i < height_s; ++i)
                delete [] primary[i];
            delete [] primary;
            delete raw;
            delete avg;
        }

        void avg_sample(){
            avg = new color_array(width, height);
            for(int i = 0; i < height_s; ++i){
                for(int j = 0; j < width_s; ++j)
                    avg->color[i/sample][j/sample] += raw->color[i][j];
            }
            for(int i = 0; i < height; ++i){
                for(int j = 0; j < width; ++j)
                    avg->color[i][j] /= (sample*sample);
            }
        }

        void render(vector<obj*> &objs, light &L, int depth){
            for(int i = 0; i < height_s; ++i){
                for(int j = 0; j < width_s; ++j)
                    raw->color[i][j] = trace(primary[i][j], objs, L, depth);
            }
            avg_sample();
        }

    private:
        void init_primary_rays(){
            vec3 unit_h = horizontal / (width_s);
            vec3 unit_v = vertical / (height_s);

            primary = new ray*[height_s];
            for(int i = 0; i < height_s; ++i){
                primary[i] = new ray[width_s];
                for(int j = 0; j < width_s; ++j)
                    primary[i][j] = ray(origin, (lowerleft + unit_h * (j+0.5) + unit_v * (i+0.5) - origin));
            }
        }
};
