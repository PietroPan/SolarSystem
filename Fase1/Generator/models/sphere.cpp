#include "sphere.h"

void midlePointsS(float radius,int slices,int stacks,vector<Point> &points,vector<Point> &normals,vector<Point2D> &texPoints){
	float stackang=(-M_PI/2),sliceang=0,x1=0,y1=0,z1=0;
    for (int i=1; i<stacks; i++){
        stackang = (-M_PI/2)+(M_PI*((float)i/stacks)); 
		for (int j=0; j<slices+1; j++){
            sliceang = 2*M_PI*((float)j/slices); 

            x1=(radius*cos(stackang)*cos(sliceang));
			y1=radius*sin(stackang);
			z1=(radius*cos(stackang)*sin(sliceang));
            points.push_back(Point(x1,y1,z1));

			x1=cos(stackang)*cos(sliceang);
			y1=sin(stackang);
			z1=cos(stackang)*sin(sliceang);

			normals.push_back(Point(x1,y1,z1));

			x1=((float)j/((float)slices));
			y1=((float)i/(float)stacks);

			texPoints.push_back(Point2D(x1,y1));

		}
	}
}

void bottomIndexsS(int slices,int i0,vector<int> &indexs){
	for (int i=0;i<slices+1;i++){
		/*if (i==slices){
			indexs.push_back(1);
			indexs.push_back(0);
        	indexs.push_back(i);
		} else {*/
        	indexs.push_back(i+1);
			indexs.push_back(0);
        	indexs.push_back(i);
		//}
    }
}

void middleIndexsS(int slices,int stacks,vector<int> &indexs){
	for (int i=0;i<stacks-2;i++){
        for (int j=0;j<slices+1;j++){
			if (j==(slices)){
				indexs.push_back((i*(slices+1))+j+1);
            	indexs.push_back((i*(slices+1))+slices+1+j+1); 
            	indexs.push_back((i*(slices+1))+j+2); 
            	indexs.push_back((i*(slices+1))+j+2);
				indexs.push_back((i*(slices+1))+1);
				indexs.push_back((i*(slices+1))+j+1);
				
			} else {
				indexs.push_back((i*(slices+1))+j+1);
            	indexs.push_back((i*(slices+1))+slices+1+j+1);
            	indexs.push_back((i*(slices+1))+slices+1+j+2);
            	indexs.push_back((i*(slices+1))+j+2);
				indexs.push_back((i*(slices+1))+j+1);
            	indexs.push_back((i*(slices+1))+slices+1+j+2);
			}
			
        }
    }
}
void topIndexsS(int slices,int stacks,vector<int> &indexs){
	int npoints = (slices+1)*(stacks-1)+2;
	for (int i=2;i<slices+2;i++){
		/*if (i==slices+1){
			indexs.push_back(npoints-i);
        	indexs.push_back(npoints-2);
        	indexs.push_back(npoints-1);
		} else {*/
			indexs.push_back(npoints-i);
        	indexs.push_back(npoints-i-1);
        	indexs.push_back(npoints-1);
		//}
    }
}

void pointsSphere(float radius,int slices,int stacks,char *filename){
    vector<int> indexs;
    vector<Point> points;
	vector<Point> normals;
	vector<Point2D> texPoints;
    
    points.push_back(Point (0,-radius,0));//bottom point
	normals.push_back(Point(0,-1,0));
	texPoints.push_back(Point2D(0.5,0));
	midlePointsS(radius,slices,stacks,points,normals,texPoints);
	points.push_back(Point(0,radius,0));//top point
	normals.push_back(Point(0,1,0));
	texPoints.push_back(Point2D(0.5,1));

	bottomIndexsS(slices,0,indexs);
	middleIndexsS(slices,stacks,indexs);
	topIndexsS(slices,stacks,indexs);

    Model model(points,indexs,normals,texPoints);
    model.writeToFile(filename,"sphere");
}
