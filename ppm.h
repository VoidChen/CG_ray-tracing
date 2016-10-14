#include<iostream>
#include<fstream>
#include<string>
using namespace std;

#ifndef vec3_h
#include"vec3.h"
#define vec3_h
#endif


class ppm{
    public:
        int width;
        int height;
        int maxcolor;
        vec3 **color;

        ppm(){
        }

        ppm(int w, int h, int mc = 255){
            width = w;
            height = h;
            maxcolor = mc;
            color = NULL;
        }

        void set_color(vec3 **c){
            color = c;
        }

        void output(string filename){
            ofstream fout;
            //fout.open(filename);
            fout.open("test.ppm");

            fout << "P3" << endl << width << " " << height << endl << maxcolor << endl;

            for(int i = height-1; i >= 0; --i){
                for(int j = 0; j < width; ++j){
                    fout << color[i][j].r << " " << color[i][j].g << " " << color[i][j].b << " ";
                }
                fout << endl;
            }

            fout.close();
        }
};
