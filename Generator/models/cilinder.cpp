#include "cilinder.h"

void basepointsCi(float radius,int slices,vector<Point> &points,vector<Point> &normals,vector<Point2D> &texcoords){;
    float ang=0,x1=0,y1=0,z1=0,theight=0,tradius=0;
		for (int j=0;j<=slices;j++){
			ang=2*M_PI*((float)j/slices);
			x1=radius*sin(ang);
			y1=0;
			z1=radius*cos(ang);
			points.push_back(Point(x1,y1,z1));
			normals.push_back(Point(0,-1,0));
			texcoords.push_back(Point2D(sin(ang)*0.1875+0.8125,cos(ang)*0.1875+0.1875));
        }
}


void toppointsCi(float radius,float height,int slices,vector<Point> &points,vector<Point> &normals,vector<Point2D> &texcoords){
    float ang=0,x1=0,y1=0,z1=0,theight=0,tradius=0;
		for (int j=0;j<=slices;j++){
			ang=2*M_PI*((float)j/slices);
			x1=radius*sin(ang);
			y1=height;
			z1=radius*cos(ang);
			points.push_back(Point(x1,y1,z1));
			normals.push_back(Point(0,1,0));
			texcoords.push_back(Point2D(sin(ang)*0.1875+0.4375,cos(ang)*0.1875+0.1875));		}
}

void middlepointsCi(float radius,float height,int slices,int stacks,vector<Point> &points,vector<Point> &normals,vector<Point2D> &texcoords){
    float ang=0,x=0,y=0,z=0;
	for (int i=0;i<=stacks;i++){
		for (int j=0;j<=slices;j++){
			ang=2*M_PI*((float)j/slices);
			x=radius*sin(ang);
			y=height*(float(i)/(float)stacks);
			z=radius*cos(ang);
            
			points.push_back(Point(x,y,z));
			x=sin(ang);
			y=0;
			z=cos(ang);
			normals.push_back(Point(x,y,z));
			texcoords.push_back(Point2D(float(j)/(float)slices,float(i)/(float)stacks*0.625+0.375));        }
	}
}

void bottomIndexsCi(int slices,vector<int> &indexs){
	for(int i=1;i<=slices;i++){
			indexs.push_back(i+1);
			indexs.push_back(i);
			indexs.push_back(0);
	}
}

void middleIndexsCi(int slices,int stacks,vector<int> &indexs){
	for (int i=0;i<stacks;i++){
		for (int j=0;j<slices;j++){
				indexs.push_back((i*(slices+1))+j+slices+1+slices+2);
				indexs.push_back((i*(slices+1))+j+slices+2);
				indexs.push_back((i*(slices+1))+j+slices+1+slices+3);

				indexs.push_back((i*(slices+1))+j+slices+2);
				indexs.push_back((i*(slices+1))+j+slices+3);
				indexs.push_back((i*(slices+1))+j+slices+1+slices+3);
		}
	}
}

void topIndexsCi(int slices,int stacks,vector<int> &indexs){
	int npoints = (slices+1)*(stacks+3)+1;
    cout << npoints;
    cout << "OI\n";
	for(int i=0;i<slices;i++){
			indexs.push_back(npoints);
			indexs.push_back(npoints-1-slices+i);
			indexs.push_back(npoints-slices+i);
	}
}

void pointsCilinder(float radius,float height,int slices,int stacks,char *filename){
    vector<int> indexs;
    vector<Point> points;
	vector<Point> normals;
	vector<Point2D> texPoints;

	points.push_back(Point(0,0,0));//bottom point
	normals.push_back(Point(0,-1,0));
    texPoints.push_back(Point2D(0.8125,0.1875));

	basepointsCi(radius,slices,points,normals,texPoints);
	middlepointsCi(radius,height,slices,stacks,points,normals,texPoints);
    toppointsCi(radius,height,slices,points,normals,texPoints);
	points.push_back(Point(0,height,0));//top point
	normals.push_back(Point(0,1,0));
	texPoints.push_back(Point2D(0.4375,0.1875));

	bottomIndexsCi(slices,indexs);
	middleIndexsCi(slices,stacks,indexs);
	topIndexsCi(slices,stacks,indexs);

    Model model(points,indexs,normals,texPoints);
    model.writeToFile(filename,"cilinder");
}
