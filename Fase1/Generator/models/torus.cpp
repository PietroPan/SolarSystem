#include "torus.h"

void pointsT(float inRadius,float outRadius,int sides,int rings,vector<Point> &points,vector<Point> &normals,vector<Point2D> &texPoints){
	float ringAng=0,sideAng=0,x=0,y=0,z=0;
    for (int i=0; i<=sides; i++){
        sideAng= (-M_PI/2) + (i * 2 * M_PI / sides);
		for (int j=0; j<=rings; j++){
            ringAng=j * 2 * M_PI / rings;

            x = (outRadius + inRadius * cos(sideAng)) * cos(ringAng);
            y = (outRadius + inRadius * cos(sideAng)) * sin(ringAng);
            z = inRadius * sin(sideAng);

            points.push_back(Point(x,z,y));
            float n[3];
            n[0]=x;
            n[1]=y;
            n[2]=z;
            normalize(n);
            normals.push_back(Point(n[0],n[2],n[1]));
            texPoints.push_back(Point2D(float(i)/float(sides),float(j)/float(rings)));
		}
	}
}


void indexsT(int sides,int rings,vector<int> &indexs){
	for (int i=0;i<sides;i++){
        for (int j=0;j<rings;j++){
            indexs.push_back(j + 1 + (i*(rings+1)) );

            indexs.push_back(j + (i*(rings+1)) );
            indexs.push_back(j + ( (i+1) * (rings+1) ));


            indexs.push_back((j+1) + ((i+1)*(rings+1)) );
            indexs.push_back(j + 1 + (i*(rings+1)) );
            indexs.push_back(j + ( (i+1) * (rings+1) ));

        }
    }
}

void pointsTorus(float inRadius,float outRadius,int sides,int rings,char *filename){
    vector<int> indexs;
    vector<Point> points;
    vector<Point> normals;
	vector<Point2D> texPoints;

	pointsT(inRadius,outRadius,sides,rings,points,normals,texPoints);
	indexsT(sides,rings,indexs);

    Model model(points,indexs,normals,texPoints);
    model.writeToFile(filename,"torus");
}