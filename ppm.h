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
        int rgb[3];
};

class ppm{
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

        void set_color(vec3 **avg){
            data = new color*[height];
            for(int i = height-1; i >= 0; --i){
                data[i] = new color[width];
                for(int j = 0; j < width; ++j){
                    for(int k = 0; k < 3; ++k){
                        data[i][j].rgb[k] = avg[i][j].data[k] >= 0 ? (avg[i][j].data[k] <= maxcolor ? avg[i][j].data[k] : maxcolor) : 0;
                    }
                }
            }
        }

        void output(string filename){
            ofstream fout;
            fout.open(filename);

            fout << "P3" << endl << width << " " << height << endl << maxcolor << endl;

            for(int i = height-1; i >= 0; --i){
                for(int j = 0; j < width; ++j){
                    for(int k = 0; k < 3; ++k)
                        fout << data[i][j].rgb[k] << " ";
                }
                fout << endl;
            }

            fout.close();
        }
};
