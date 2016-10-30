#include<iostream>
#include<fstream>
#ifndef vec3_h
#include"vec3.h"
#define vec3_h
#endif
using namespace std;

class BGRA{
    public:
        char data[4];

        BGRA(){
        }
};

class bitmap_header{
    public:
        short sig;
        unsigned int size;
        int reserved;
        unsigned int offset;

        bitmap_header(unsigned int w, unsigned int h){
            sig = 0x4D42;
            size = 14 + 40 + w*h * 4;
            reserved = 0x00000000;
            offset = 54;
        }

        void output(ofstream &fout){
            fout.write((char*)&sig, sizeof(sig));
            fout.write((char*)&size, sizeof(size));
            fout.write((char*)&reserved, sizeof(reserved));
            fout.write((char*)&offset, sizeof(offset));
        }
};

class DIB_header{
    public:
        unsigned int header_size;
        unsigned int width;
        unsigned int height;
        short plane;
        short bits;
        unsigned int compression;
        unsigned int image_size;
        unsigned int horizontal;
        unsigned int vertical;
        unsigned int palette;
        unsigned int important;

        DIB_header(unsigned int w, unsigned int h){
            header_size = 40;
            width = w;
            height = h;
            plane = 1;
            bits = 32;
            compression = 0;
            image_size = width * height * bits/8;
            horizontal = 12000;
            vertical = 12000;
            palette = 0;
            important = 0;
        }

        void output(ofstream &fout){
            fout.write((char*)this, sizeof(DIB_header));
        }
};

class pixel_data{
    public:
        BGRA **data;
        unsigned int width;
        unsigned int height;

        pixel_data(unsigned int w, unsigned int h, vec3 **c){
            width = w;
            height = h;
            data = new BGRA*[height];
            for(int i = height-1; i >= 0; --i){
                data[i] = new BGRA[width];
                for(unsigned int j = 0; j < width; ++j){
                    for(int k = 0; k < 3; ++k)
                        data[i][j].data[2-k] = c[i][j].data[k] >= 0 ? (c[i][j].data[k] <= 255 ? c[i][j].data[k] : 255) : 0;
                    data[i][j].data[3] = 100;
                }
            }
        }

        ~pixel_data(){
            //TBD
        }

        void output(ofstream &fout){
            for(unsigned int i = 0; i < height; ++i){
                for(unsigned int j = 0; j < width; ++j){
                    fout.write((char*)data[i][j].data, sizeof(BGRA));
                }
            }
        }
};

class BMP{
    public:
        bitmap_header *bh;
        DIB_header *dh;
        pixel_data *pd;

        BMP(int width, int height, vec3 **color){
            bh = new bitmap_header(width, height);
            dh = new DIB_header(width, height);
            pd = new pixel_data(width, height, color);
        }

        ~BMP(){
            delete bh;
            delete dh;
            delete pd;
        }

        void output(string filename){
            ofstream fout;
            fout.open(filename, ios::binary);

            bh->output(fout);
            dh->output(fout);
            pd->output(fout);

            fout.close();
        }
};
