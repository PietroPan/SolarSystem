#ifndef GENERATOR_CILINDER_H
#define GENERATOR_CILINDER_H

#include <math.h>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "../utils/point.h"
#include "../utils/model.h"

void pointsCilinder(float radius,float height,int slices,int stacks,char *filename);
void basepointsCi(float radius,int slices,vector<Point> &points,vector<Point> &normals,vector<Point2D> &texcoords);
void toppointsCi(float radius,float height,int slices,vector<Point> &points,vector<Point> &normals,vector<Point2D> &texcoords);
void middlepointsCi(float radius,float height,int slices,int stacks,vector<Point> &points,vector<Point> &normals,vector<Point2D> &texcoords);
void bottomIndexsCi(int slices,vector<int> &indexs);
void middleIndexsCi(int slices,int stacks,vector<int> &indexs);
void topIndexsCi(int slices,int stacks,vector<int> &indexs);


#endif