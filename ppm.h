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
    public:
        int width;
        int height;
        int maxcolor;
        color **data;

        ppm(){
        }

        ppm(int w, int h, int mc = 255){
            width = w;
            height = h;
            maxcolor = mc;
            data = NULL;
        }

        void set_color(vec3 **c, int sample){
            data = new color*[height];
            for(int i = height-1; i >= 0; --i){
                data[i] = new color[width];
                for(int j = 0; j < width; ++j){
                    vec3  avg= vec3(0, 0, 0);
                    for(int k = i*sample; k < (i+1)*sample; ++k){
                        for(int l = j*sample; l < (j+1)*sample; ++l)
                            avg = avg + c[k][l];
                    }
                    avg = avg / (sample*sample);

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
