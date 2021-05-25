#ifndef GENERATOR_MODEL_H
#define GENERATOR_MODEL_H

#include <vector>
#include <fstream>
#include <iosfwd>
#include "point.h"
#include "point2D.h"

using namespace std;

class Model{
private:
    vector<Point> points;
    vector<int> indexs;
    vector<Point> normals;
    vector<Point2D> texPoints;
public:
    Model() {}

    Model(vector<Point> points,vector<int> indexs,vector<Point> normals,vector<Point2D>texPoints){
        this->points=points;
        this->indexs=indexs;
        this->normals=normals;
        this->texPoints=texPoints;
    }

    Model(vector<Point> points,vector<Point> normals,vector<Point2D> texPoints){
        this->points=points;
        this->normals=normals;
        this->texPoints=texPoints;
    }

    void writeToFile(char *filename,char const *tag);
    void writeTToFile(char *filename,char const *tag,int w,int h);
};

#endif