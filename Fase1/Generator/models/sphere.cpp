#include "sphere.h"

void midlePointsS(float radius,int slices,int stacks,vector<Point> &points){
	float stackang=0,sliceang=0,x1=0,y1=0,z1=0;
    for (int i=1; i<stacks; i++){
        stackang = (-M_PI/2)+(M_PI*((float)i/stacks)); 
		for (int j=0; j<slices; j++){
            sliceang = 2*M_PI*((float)j/slices); 
            x1=(radius*cos(stackang)*cos(sliceang));
			z1=(radius*cos(stackang)*sin(sliceang));
			y1=radius*sin(stackang);
            points.push_back(Point(x1,y1,z1));


		}
	}
}

void bottomIndexsS(int slices,int i0,vector<int> &indexs){
	for (int i=0;i<slices+1;i++){
		if (i==slices){
			indexs.push_back(1);
			indexs.push_back(0);
        	indexs.push_back(i);
		} else {
        	indexs.push_back(i+1);
			indexs.push_back(0);
        	indexs.push_back(i);
		}
    }
}

void middleIndexsS(int slices,int stacks,vector<int> &indexs){
	for (int i=0;i<(stacks-2);i++){
        for (int j=0;j<slices;j++){
			if (j==(slices-1)){
				indexs.push_back((i*slices)+j+1);
            	indexs.push_back((i*slices)+slices+j+1); 
            	indexs.push_back((i*slices)+j+2); 
            	indexs.push_back((i*slices)+j+2);
				indexs.push_back((i*slices)+1);
				indexs.push_back((i*slices)+j+1);
				
			} else {
				indexs.push_back((i*slices)+j+1);
            	indexs.push_back((i*slices)+slices+j+1);
            	indexs.push_back((i*slices)+slices+j+2);
            	indexs.push_back((i*slices)+j+2);
				indexs.push_back((i*slices)+j+1);
            	indexs.push_back((i*slices)+slices+j+2);
			}
			
        }
    }
}

void topIndexsS(int slices,int stacks,vector<int> &indexs){
	int npoints = slices*(stacks-1)+2;
	for (int i=2;i<slices+2;i++){
		if (i==slices+1){
			indexs.push_back(npoints-i);
        	indexs.push_back(npoints-2);
        	indexs.push_back(npoints-1);
		} else {
			indexs.push_back(npoints-i);
        	indexs.push_back(npoints-i-1);
        	indexs.push_back(npoints-1);
		}
    }
}

void pointsSphere(float radius,int slices,int stacks,char *filename){
    vector<int> indexs;
    vector<Point> points;
    
    points.push_back(Point (0,-radius,0));//bottom point
	midlePointsS(radius,slices,stacks,points);
	points.push_back(Point(0,radius,0));//top point

	bottomIndexsS(slices,0,indexs);
	middleIndexsS(slices,stacks,indexs);
	topIndexsS(slices,stacks,indexs);

    Model model(points,indexs);
    model.writeToFile(filename,"sphere");
}
