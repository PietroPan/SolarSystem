#ifndef GENERATOR_POINT2D_H
#define GENERATOR_POINT2D_H
#include <string>

using namespace std;

class Point2D {
    private:
        float x,y;
    public:
        Point2D(float x,float y){
            this->x=x;
            this->y=y;
        }

        float getX(){
            return this->x;
        }

        float getY(){
            return this->y;
        }

        string point_to_string(){return to_string(this->x)+" "+to_string(this->y);}
};




#endif