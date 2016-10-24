#include<iostream>
#include<fstream>
#include<string>
#ifndef vec3_h
#include"vec3.h"
#define vec3_h
#endif
using namespace std;

class color{
    public:
        int r;
        int g;
        int b;
};

class ppm{
    private:
        vec3 avg_sample(vec3 **c, int h, int w, int sample){
            vec3 result = vec3(0, 0, 0);
            for(int i = h*sample; i < (h+1)*sample; ++i){
                for(int j = w*sample; j < (w+1)*sample; ++j)
                    result = result + c[i][j];
            }
            return result / (sample*sample);
        }

    public:
        int width;
        int height;
        int maxcolor;
        color **data;

        ppm(int w, int h, int mc = 255){
            width = w;
            height = h;
            maxcolor = mc;
            data = NULL;
        }

        ~ppm(){
            if(data != NULL){
                for(int i = 0; i < height; ++i)
                    delete [] data[i];
                delete [] data;
            }
        }

        void set_color(vec3 **c, int sample){
            vec3 avg;

            data = new color*[height];
            for(int i = height-1; i >= 0; --i){
                data[i] = new color[width];
                for(int j = 0; j < width; ++j){
                    avg = avg_sample(c, i, j, sample);
                    data[i][j].r = avg.r >= 0 ? (avg.r <= maxcolor ? avg.r : maxcolor) : 0;
                    data[i][j].g = avg.g >= 0 ? (avg.g <= maxcolor ? avg.g : maxcolor) : 0;
                    data[i][j].b = avg.b >= 0 ? (avg.b <= maxcolor ? avg.b : maxcolor) : 0;
                }
            }
        }

        void output(string filename){
            ofstream fout;
            fout.open(filename.c_str());

            fout << "P3" << endl << width << " " << height << endl << maxcolor << endl;

            for(int i = height-1; i >= 0; --i){
                for(int j = 0; j < width; ++j)
                    fout << data[i][j].r << " " << data[i][j].g << " " << data[i][j].b << " ";
                fout << endl;
            }

            fout.close();
        }
};
