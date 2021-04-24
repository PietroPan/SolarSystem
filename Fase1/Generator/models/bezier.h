#ifndef GENERATOR_BEZIER_H
#define GENERATOR_BEZIER_H

#include "../utils/model.h"
#include <math.h>
#include "../utils/point.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <map>
#include <limits>
#include <regex>

vector<vector<float>> preCalculate(int h,vector<int> &patch,vector<float> &points);

void calculateIndexes(int n,int tess,vector<unsigned int> &ind);

void calculatePatches(int tess,vector<float> &iPoints,vector<vector<int>> &iPatches,vector<float> &p);

void readFile(string nameOF,vector<float> &points,vector<vector<int>> &patches);

void pointsBezier(char* inpFile,int tess,char* outFile);

#endif