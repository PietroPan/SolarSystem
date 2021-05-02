#ifndef GENERATOR_MODEL_H
#define GENERATOR_MODEL_H

#include <vector>
#include <fstream>
#include <iosfwd>
#include "point.h"

using namespace std;

class Model{
private:
    vector<Point> points;
    vector<int> indexs;
public:
    Model() {}

    Model(vector<Point> points,vector<int> indexs){
        this->points=points;
        this->indexs=indexs;
    }

    Model(vector<Point> points){
        this->points=points;
    }

    void writeToFile(char *filename,char const *tag);
    void writeTToFile(char *filename,char const *tag,int w,int h);
};

#endif