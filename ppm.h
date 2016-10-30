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
    private:
        vec3** avg_sample(vec3 **c, int sample){
            vec3 **result;
            result = new vec3*[height];
            for(int i = 0; i < height; ++i){
                result[i] = new vec3[width];
                for(int j = 0; j < width; ++j){
                    result[i][j] = vec3(0, 0, 0);
                    for(int k = i*sample; k < (i+1)*sample; ++k){
                        for(int l = j*sample; l < (j+1)*sample; ++l){
                            result[i][j] = result[i][j] + c[k][l];
                        }
                    }
                    result[i][j] = result[i][j] / (sample*sample);
                }
            }
            return result;
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
            vec3 **avg = avg_sample(c, sample);
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
