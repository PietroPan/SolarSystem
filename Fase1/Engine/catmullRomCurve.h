#ifndef ENGINE_CATMULLROMCURVE_H
#define ENGINE_CATMULLROMCURVE_H

#include "gereIncludes.h"

void multMatrixVector(float *m, float *v, float *res);
void getCatmullRomPoint(float t, vector<float> p0, vector<float> p1, vector<float> p2, vector<float> p3, float *pos, float *deriv);
void getGlobalCatmullRomPoint(float gt, float *pos, float *deriv,vector<vector<float>> points);
void renderCatmullRomCurve(vector<vector<float>> points);
void cross(float *a, float *b, float *res);
void normalize(float *a);
void catmullRomTranslate(float time,vector<vector<float>> points,float* yAxis);

#endif 