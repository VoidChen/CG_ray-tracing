#include<iostream>
#include<cmath>
using namespace std;

class vec3{
    private:
        double data[3];

    public:
        double &x, &y, &z;
        double &r, &g, &b;

        vec3(): x(data[0]), y(data[1]), z(data[2]), r(data[0]), g(data[1]), b(data[2]) {
        }

        vec3& operator= (const vec3 &v){
            for(int i = 0; i < 3; ++i)
                this->data[i] = v.data[i];

            return *this;
        }

        vec3 operator+ (const vec3 &v){
            vec3 result;
            for(int i = 0; i < 3; ++i)
                result.data[i] = this->data[i] + v.data[i];

            return result;
        }

        vec3 operator- (const vec3 &v){
            vec3 result;
            for(int i = 0; i < 3; ++i)
                result.data[i] = this->data[i] - v.data[i];

            return result;
        }

        vec3 operator* (const double &s){
            vec3 result;
            for(int i = 0; i < 3; ++i)
                result.data[i] = this->data[i] * s;

            return result;
        }

        vec3 operator/ (const double &s){
            vec3 result;
            for(int i = 0; i < 3; ++i)
                result.data[i] = this->data[i] / s;

            return result;
        }

        static double dot(const vec3 &v1, const vec3 &v2){
            double result = 0;
            for(int i = 0; i < 3; ++i)
                result += v1.data[i] * v2.data[i];

            return result;
        }

        static vec3 cross(const vec3 &v1, const vec3 &v2){
            vec3 result;
            for(int i = 0; i < 3; ++i){
                result.data[i] = v1.data[(i+1)%3]*v2.data[(i+2)%3] - v1.data[(i+2)%3]*v2.data[(i+1)%3];
            }

            return result;
       }

        double length(){
            double result = 0;
            for(int i = 0; i < 3; ++i)
                result += this->data[i] * this->data[i];

            return sqrt(result);
        }

        vec3 unit(){
            return (*this)/this->length();
        }

};

int main(){
    vec3 point1, point2, point3, point4;
    point1.x = 1;
    point1.y = 3;
    point1.z = -5;

    point2.r = 4;
    point2.g = -2;
    point2.b = -1;

    point3 = point1 + point2;
    cout << point3.x << " " << point3.y << " " << point3.z <<endl;

    point3 = point1 - point2;
    cout << point3.x << " " << point3.y << " " << point3.z <<endl;

    point3 = point1 * 10;
    cout << point3.x << " " << point3.y << " " << point3.z <<endl;

    point3 = point1 / 10;
    cout << point3.x << " " << point3.y << " " << point3.z <<endl;

    cout << vec3::dot(point1, point2) <<endl;

    point3 = vec3::cross(point1, point2);
    cout << point3.x << " " << point3.y << " " << point3.z <<endl;

    cout << point1.length() <<endl;

    point3 = point1.unit();
    cout << point3.x << " " << point3.y << " " << point3.z <<endl;

    return 0;
}
