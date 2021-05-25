#ifndef GENERATOR_BOX_H
#define GENERATOR_BOX_H

#include "../utils/model.h"
#include <math.h>
#include "../utils/point.h"

void xzPlane(float x0,float y0,float z0,float xinc,float zinc,int steps,vector<Point> &points,vector<Point> &normals,vector<Point2D> &texPoints);

void zyPlane(float x0,float y0,float z0,float yinc,float zinc,int steps,vector<Point> &points,vector<Point> &normals,vector<Point2D> &texPoints);

void yxPlane(float x0,float y0,float z0,float xinc,float yinc,int steps,vector<Point> &points,vector<Point> &normals,vector<Point2D> &texPoints);

void calcInds(int i0,int steps,vector<int> &indexs);

void calcInds2(int i0,int steps,vector<int> &indexs);

void pointsBox(float x,float y,float z,int divs,char *filename);

#endif