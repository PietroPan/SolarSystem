#include "box.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <map>
#include <math.h>
#include <limits>

using namespace std;

void xzPlane(float x0,float y0,float z0,float xinc,float zinc,int steps,vector<Point> &points){
	for (int i=0;i<steps;i++){
		for (int j=0;j<steps;j++) points.push_back(Point(x0+j*xinc,y0,z0+i*zinc));
	}
}

void zyPlane(float x0,float y0,float z0,float yinc,float zinc,int steps,vector<Point> &points){
	for (int i=0;i<steps;i++){
		for (int j=0;j<steps;j++) points.push_back(Point(x0,y0+i*yinc,z0+j*zinc));
	}
}

void yxPlane(float x0,float y0,float z0,float xinc,float yinc,int steps,vector<Point> &points){
	for (int i=0;i<steps;i++){
		for (int j=0;j<steps;j++) points.push_back(Point(x0+j*xinc,y0+i*yinc,z0));
	}
}

void calcInds(int i0,int steps,vector<int> &indexs){
	for (int i=0;i<steps;i++){
		for (int j=0;j<steps;j++){
			indexs.push_back(i0+j+i*(steps+1));
			indexs.push_back(i0+(j+1)+i*(steps+1));
			indexs.push_back(i0+(j+1)+(i+1)*(steps+1));

			indexs.push_back(i0+j+i*(steps+1));
			indexs.push_back(i0+(j+1)+(i+1)*(steps+1));
			indexs.push_back(i0+j+(i+1)*(steps+1));
		}
	}
}

void calcInds2(int i0,int steps,vector<int> &indexs){
	for (int i=0;i<steps;i++){
		for (int j=0;j<steps;j++){
			indexs.push_back(i0+(j+1)+i*(steps+1));
			indexs.push_back(i0+j+i*(steps+1));
			indexs.push_back(i0+(j+1)+(i+1)*(steps+1));

			indexs.push_back(i0+(j+1)+(i+1)*(steps+1));
			indexs.push_back(i0+j+i*(steps+1));
			indexs.push_back(i0+j+(i+1)*(steps+1));
		}
	}
}

void pointsBox(float x,float y,float z,int divs,char *filename){
    vector<int> indexs;
    vector<Point> points;
	float x0=-(x/2),y0=-(y/2),z0=-(z/2);
	float xinc=x/divs,yinc=y/divs,zinc=z/divs;
	int numPlanePoints=pow(divs+1,2),j=0;

	xzPlane(x0,y0,z0,xinc,zinc,divs+1,points);
	zyPlane(x0,y0,z0,yinc,zinc,divs+1,points);
	yxPlane(x0,y0,z0+z,xinc,yinc,divs+1,points);
	xzPlane(x0,y0+y,z0,xinc,zinc,divs+1,points);
	zyPlane(x0+x,y0,z0,yinc,zinc,divs+1,points);
	yxPlane(x0,y0,z0,xinc,yinc,divs+1,points);

	for (int i=0;i<3;i++,j+=numPlanePoints) calcInds(j,divs,indexs);
	for (int i=0;i<3;i++,j+=numPlanePoints) calcInds2(j,divs,indexs);
    Model model(points,indexs);
    model.writeToFile(filename,"box");
}
