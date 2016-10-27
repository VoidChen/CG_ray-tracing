#include<cmath>

class vec3{
    public:
        double data[3];
        double &x, &y, &z;
        double &r, &g, &b;

        vec3(): x(data[0]), y(data[1]), z(data[2]), r(data[0]), g(data[1]), b(data[2]) {
        }

        vec3(double d0, double d1, double d2): x(data[0]), y(data[1]), z(data[2]), r(data[0]), g(data[1]), b(data[2]) {
            data[0] = d0;
            data[1] = d1;
            data[2] = d2;
        }

        vec3& operator= (const vec3 &v){
            for(int i = 0; i < 3; ++i)
                this->data[i] = v.data[i];

            return *this;
        }

        bool operator!= (const vec3 &v){
            for(int i = 0; i < 3; ++i){
                if(this->data[i] != v.data[i])
                    return true;
            }

            return false;
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
            for(int i = 0; i < 3; ++i)
                result.data[i] = v1.data[(i+1)%3]*v2.data[(i+2)%3] - v1.data[(i+2)%3]*v2.data[(i+1)%3];

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
