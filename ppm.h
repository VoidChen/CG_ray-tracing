#include<iostream>
#include<fstream>
#include<string>
#ifndef vec3_h
#include"vec3.h"
#define vec3_h
#endif
using namespace std;

class PPM{
    private:
        class RGB{
            public:
                int rgb[3];
        };

    public:
        int width;
        int height;
        int maxcolor;
        RGB **data;

        PPM(int w, int h, vec3 **ca, int mc = 255){
            width = w;
            height = h;
            maxcolor = mc;
            data = new RGB*[height];
            for(int i = height-1; i >= 0; --i){
                data[i] = new RGB[width];
                for(int j = 0; j < width; ++j){
                    for(int k = 0; k < 3; ++k){
                        data[i][j].rgb[k] = ca[i][j].data[k] >= 0 ? (ca[i][j].data[k] <= maxcolor ? ca[i][j].data[k] : maxcolor) : 0;
                    }
                }
            }
        }

        ~PPM(){
            for(int i = 0; i < height; ++i)
                delete [] data[i];
            delete [] data;
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
