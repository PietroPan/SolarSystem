#include "box.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <map>
#include <math.h>
#include <limits>

using namespace std;

void xzPlane(float x0,float y0,float z0,float xinc,float zinc,int steps,vector<Point> &points,vector<Point> &normals,vector<Point2D> &texPoints,bool rep,bool invert){
	for (int i=0;i<steps;i++){
		for (int j=0;j<steps;j++){
			points.push_back(Point(x0+j*xinc,y0,z0+i*zinc));
			if (y0<0){
				if (invert) normals.push_back(Point(0,1,0));
				else normals.push_back(Point(0,-1,0));
				if (rep) texPoints.push_back(Point2D(i%2,j%2));				
					else texPoints.push_back(Point2D((float(i)/float(steps-1))*0.25+0.25,(1.0f/3.0f)-(float(j)/float(steps-1))*(1.0f/3.0f)));
			} else {
				if (rep) texPoints.push_back(Point2D(i%2 ,j%2));					
				else texPoints.push_back(Point2D( (float(i)/float(steps-1))*0.25+0.25 ,(float(j)/float(steps-1))*(1.0f/3.0f)+(2.0f/3.0f) ));
				if (invert) normals.push_back(Point(0,-1,0));
				else normals.push_back(Point(0,1,0));
			}
		}
	}
}

void zyPlane(float x0,float y0,float z0,float yinc,float zinc,int steps,vector<Point> &points,vector<Point> &normals,vector<Point2D> &texPoints,bool rep, bool invert){
	for (int i=0;i<steps;i++){
		for (int j=0;j<steps;j++){
			 points.push_back(Point(x0,y0+i*yinc,z0+j*zinc));
			if (x0<0){
				if (invert) normals.push_back(Point(1,0,0));
				else normals.push_back(Point(-1,0,0));
				if (rep) texPoints.push_back(Point2D(i%2,j%2));
				else texPoints.push_back(Point2D((float(j)/float(steps-1))*0.25+0.25,(float(i)/float(steps-1))*(1.0f/3.0f)+(1.0f/3.0f)));
			} else {
				if (invert) normals.push_back(Point(-1,0,0));
				else normals.push_back(Point(1,0,0));
				if (rep) texPoints.push_back(Point2D(i%2,j%2));
				else texPoints.push_back(Point2D(1-(float(j)/float(steps-1))*0.25,(float(i)/float(steps-1))*(1.0f/3.0f)+(1.0f/3.0f)));
			}

			
		}
		

	}
}

void yxPlane(float x0,float y0,float z0,float xinc,float yinc,int steps,vector<Point> &points,vector<Point> &normals,vector<Point2D> &texPoints,bool rep, bool invert){
	for (int i=0;i<steps;i++){
		for (int j=0;j<steps;j++) {
			points.push_back(Point(x0+j*xinc,y0+i*yinc,z0));
			if (z0<0){
				if (invert) normals.push_back(Point(0,0,1));
				else normals.push_back(Point(0,0,-1));
				if (rep) texPoints.push_back(Point2D(i%2,j%2));
				else texPoints.push_back(Point2D(0.25-(float(j)/float(steps-1))*0.25,(float(i)/float(steps-1))*(1.0f/3.0f)+(1.0f/3.0f)));
				
			} else {
				if (invert) normals.push_back(Point(0,0,-1));
				else normals.push_back(Point(0,0,1));
				if (rep) texPoints.push_back(Point2D(i%2,j%2));
				else texPoints.push_back(Point2D((float(j)/float(steps-1))*0.25+0.5,(float(i)/float(steps-1))*(1.0f/3.0f)+(1.0f/3.0f)));
			}
		}
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

void calcInvInds(int i0,int steps,vector<int> &indexs){
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

void calcInvInds2(int i0,int steps,vector<int> &indexs){
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

void pointsBox(float x,float y,float z,int divs,char *filename,bool invert,bool rep){
    vector<int> indexs;
    vector<Point> points;
    vector<Point> normals;
	vector<Point2D> texPoints;
	float x0=-(x/2),y0=-(y/2),z0=-(z/2);
	float xinc=x/divs,yinc=y/divs,zinc=z/divs;
	int numPlanePoints=pow(divs+1,2),j=0;

	xzPlane(x0,y0,z0,xinc,zinc,divs+1,points,normals,texPoints,rep,invert);
	zyPlane(x0,y0,z0,yinc,zinc,divs+1,points,normals,texPoints,rep,invert);
	yxPlane(x0,y0,z0+z,xinc,yinc,divs+1,points,normals,texPoints,rep,invert);
	xzPlane(x0,y0+y,z0,xinc,zinc,divs+1,points,normals,texPoints,rep,invert);
	zyPlane(x0+x,y0,z0,yinc,zinc,divs+1,points,normals,texPoints,rep,invert);
	yxPlane(x0,y0,z0,xinc,yinc,divs+1,points,normals,texPoints,rep,invert);

	if (invert) {
		for (int i=0;i<3;i++,j+=numPlanePoints) calcInvInds(j,divs,indexs);
		for (int i=0;i<3;i++,j+=numPlanePoints) calcInvInds2(j,divs,indexs);
	} else {
		for (int i=0;i<3;i++,j+=numPlanePoints) calcInds(j,divs,indexs);
		for (int i=0;i<3;i++,j+=numPlanePoints) calcInds2(j,divs,indexs);
	}
    Model model(points,indexs,normals,texPoints);
    model.writeToFile(filename,"box");
}
