#ifndef GENERATOR_POINT_H
#define GENERATOR_POINT_H
#include <string>

using namespace std;

class Point {
    private:
        float x,y,z;
    public:
        Point(float x,float y,float z){
            this->x=x;
            this->y=y;
            this->z=z;
        }

        float getX(){
            return this->x;
        }

        float getY(){
            return this->y;
        }

        float getZ(){
            return this->z;
        }
        string point_to_string(){return to_string(this->x)+" "+to_string(this->y)+" "+to_string(this->z);}
};




#endif