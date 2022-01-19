#ifndef GENERATOR_TORUS_H
#define GENERATOR_TORUS_H

#include <math.h>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "../utils/point.h"
#include "../utils/model.h"
#include "terrain.h"

void pointsT(float inRadius,float outRadius,int sides,int rings,vector<Point> &points,vector<Point> &normals,vector<Point2D> &texPoints);
void indexsT(int sides,int rings,vector<int> &indexs);
void pointsTorus(float inRadius,float outRadius,int sides,int rings,char *filename);

#endif