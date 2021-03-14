#ifndef GENERATOR_SPHERE_H
#define GENERATOR_SPHERE_H

#include <math.h>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "../utils/point.h"
#include "../utils/model.h"


void topIndexsS(int slices,int stacks,vector<int> &indexs);
void midlePointsS(float radius,int slices,int stacks,vector<Point> &points);
void bottomIndexsS(int slices,int i0,vector<int> &indexs);
void middleIndexsS(int slices,int stacks,vector<int> &indexs);
void pointsSphere(float radius,int slices,int stacks,char *filename);

#endif
