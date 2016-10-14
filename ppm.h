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

        void set_color(vec3 **c){
            data = new color*[height];
            for(int i = height-1; i >= 0; --i){
                data[i] = new color[width];
                for(int j = 0; j < width; ++j){
                    data[i][j].r = c[i][j].r >= 0 ? (c[i][j].r <= maxcolor ? c[i][j].r : maxcolor) : 0;
                    data[i][j].g = c[i][j].g >= 0 ? (c[i][j].g <= maxcolor ? c[i][j].g : maxcolor) : 0;
                    data[i][j].b = c[i][j].b >= 0 ? (c[i][j].b <= maxcolor ? c[i][j].b : maxcolor) : 0;
                }
            }
        }

        void output(string filename){
            ofstream fout;
            fout.open(filename);

            fout << "P3" << endl << width << " " << height << endl << maxcolor << endl;

            for(int i = height-1; i >= 0; --i){
                for(int j = 0; j < width; ++j){
                    fout << data[i][j].r << " " << data[i][j].g << " " << data[i][j].b << " ";
                }
                fout << endl;
            }

            fout.close();
        }
};
