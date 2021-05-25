#include "cone.h"

void middlepointsC(float radius,float height,int slices,int stacks,vector<Point> &points){
	float ang=0,x1=0,y1=0,z1=0,theight=0,tradius=0,ia=stacks;
	float alfac = (atan(height/radius));
	float heightinc = height/stacks;
	float radiusdec = heightinc*tan((M_PI/2)-alfac);
	for (int i=0;i<stacks;i++,ia--){
		theight=i*heightinc;
		tradius=radiusdec*ia;
		for (int j=0;j<slices;j++){
			ang=2*M_PI*((float)j/slices);
			x1=tradius*sin(ang);
			y1=theight;
			z1=tradius*cos(ang);
			points.push_back(Point(x1,y1,z1));
		}
	}
}

void bottomIndexsC(int slices,vector<int> &indexs){
	for(int i=1;i<slices+1;i++){
		if (i==slices){
			indexs.push_back(1);
			indexs.push_back(i);
			indexs.push_back(0);
		} else {
			indexs.push_back(i+1);
			indexs.push_back(i);
			indexs.push_back(0);
		}
	}
}

void middleIndexsC(int slices,int stacks,vector<int> &indexs){
	for (int i=0;i<stacks-1;i++){
		for (int j=0;j<slices;j++){
			if (j==(slices-1)){
				if (i==0){

				}
				indexs.push_back((i*slices)+j+slices+1);
				indexs.push_back((i*slices)+j+1);
				indexs.push_back((i*slices)+j+2);

				indexs.push_back((i*slices)+j+1);
				indexs.push_back((i*slices)+1);
				indexs.push_back((i*slices)+j+2);
			} else {
				indexs.push_back((i*slices)+j+slices+1);
				indexs.push_back((i*slices)+j+1);
				indexs.push_back((i*slices)+j+slices+2);

				indexs.push_back((i*slices)+j+1);
				indexs.push_back((i*slices)+j+2);
				indexs.push_back((i*slices)+j+slices+2);
			}
		}
	}
}

void topIndexsC(int slices,int stacks,vector<int> &indexs){
	int npoints = slices*stacks+1;
	for(int i=0;i<slices;i++){
		if (i==slices){
			indexs.push_back(npoints);
			indexs.push_back(npoints-1-slices+i);
			indexs.push_back(npoints-1-slices);
		} else {
			indexs.push_back(npoints);
			indexs.push_back(npoints-1-slices+i);
			indexs.push_back(npoints-slices+i);
		}
	}
}

void pointsCone(float radius,float height,int slices,int stacks,char *filename){
    vector<int> indexs;
    vector<Point> points;
	vector<Point> normals;
	vector<Point2D> texPoints;

	points.push_back(Point(0,0,0));//bottom point
	middlepointsC(radius,height,slices,stacks,points);
	points.push_back(Point(0,height,0));//top point

	bottomIndexsC(slices,indexs);
	middleIndexsC(slices,stacks,indexs);
	topIndexsC(slices,stacks,indexs);

    Model model(points,indexs,normals,texPoints);
    model.writeToFile(filename,"cone");
}
