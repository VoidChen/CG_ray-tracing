#include<iostream>
#include<fstream>
using namespace std;

int main(){
    int width = 800;
    int height = 600;
    int maxcolor = 255;

    ofstream fout;
    fout.open("test.ppm");

    fout << "P3" << endl << width << " " << height << endl << maxcolor << endl;

    for(int i = 0; i < height; ++i){
        for(int j = 0; j < width; ++j){
            fout << min(255*i/height, 255) << " " << 255 << " " << 255 << " ";
        }
        fout << endl;
    }

    fout.close();

    return 0;
}
