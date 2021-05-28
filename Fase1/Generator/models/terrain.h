#ifndef GENERATOR_TERRAIN_H
#define GENERATOR_TERRAIN_H

#include <math.h>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "../utils/point.h"
#include "../utils/model.h"
#include <IL/il.h>


void drawGrid(int h,int w,vector<Point> &p,unsigned char* c,float mult);
void pointsTerrain(char *, char *,float mult);
void cross(float *a, float *b, float *res);
void normalize(float *a);
void sub (float *a, float *b, float *res);
void computeNormal(int i, int j,int w,unsigned char* c,vector<Point> &normal,float mult);

#endif