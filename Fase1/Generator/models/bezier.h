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

vector<vector<float>> preCalculate(char coord,vector<int> &patch,vector<Point> &points);

void calculateIndexes(int n,int tess,vector<int> &ind);

void calculatePatches(int tess,vector<Point> &iPoints,vector<vector<int>> &iPatches,vector<Point> &p);

void readFile(string nameOF,vector<Point> &points,vector<vector<int>> &patches);

void pointsBezier(char* inpFile,int tess,char* outFile);

#endif