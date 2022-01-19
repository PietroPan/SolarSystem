#ifndef GENERATOR_CONE_H
#define GENERATOR_CONE_H

#include <math.h>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "../utils/point.h"
#include "../utils/model.h"

void basepointsC(float radius,int slices,vector<Point> &points,vector<Point> &normals,vector<Point2D> &texcoords);
void middlepointsC(float radius,float height,int slices,int stacks,vector<Point> &points,vector<Point> &normals,vector<Point> &texcoords);
void bottomIndexsC(int slices,vector<int> &indexs);
void middleIndexsC(int slices,int stacks,vector<int> &indexs);
void topIndexsC(int slices,int stacks,vector<int> &indexs);
void pointsCone(float radius,float height,int slices,int stacks,char *filename);

#endif