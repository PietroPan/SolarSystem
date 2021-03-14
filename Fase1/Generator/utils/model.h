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

    void writeToFile(char *filename,char const *tag);
};

#endif