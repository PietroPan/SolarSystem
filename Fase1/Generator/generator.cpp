#include <iostream>
#include <fstream>
#include <cstring>
#include <map>
#include <math.h>
#include <limits>
using namespace std;


void create_plane (float length, float width, string file_name) {
  // Create and open a text file
 ofstream MyFile(file_name);

 // Write to the file
 MyFile << "Plane\n";
 MyFile << "4\n";

 //Pontos do primeiro triangulo
 string point0 = to_string(length/2) + " 0 " + to_string(width/2) + "\n";
 MyFile << point0;

 string point1 = to_string(length/2) + " 0 " + to_string(-width/2) + "\n";
 MyFile << point1;

 string point2 = to_string(-length/2) + " 0 " + to_string(-width/2) + "\n";
 MyFile << point2;

 string point3 = to_string(-length/2) + " 0 " + to_string(width/2) + "\n";
 MyFile << point3;

 MyFile << "0\n";
 MyFile << "1\n";
 MyFile << "2\n";
 MyFile << "2\n";
 MyFile << "3\n";
 MyFile << "0\n";

 // Close the file
 MyFile.close();
}


string pto_string(float x,float y,float z){
    return to_string(x)+" "+to_string(y)+" "+to_string(z)+"\n";
}

void create_sphere(float radius,int slices,int stacks,string file){
    ofstream MyFile(file);
    MyFile << "sphere\n";
    int npoints = slices*(stacks-1)+2;
    MyFile << to_string(npoints)+"\n";

    float stackang=0,sliceang=0,x1=0,y1=0,z1=0;
    MyFile << pto_string(0,-radius,0);

    for (int i=1; i<stacks; i++){
        stackang = (-M_PI/2)+(M_PI*((float)i/stacks));

        for (int j=0; j<slices; j++){
            sliceang = 2*M_PI*((float)j/slices);
            x1=(radius*cos(stackang)*cos(sliceang));
			z1=(radius*cos(stackang)*sin(sliceang));
			y1=radius*sin(stackang);
            MyFile << pto_string(x1,y1,z1);
        }
    }
    MyFile << pto_string(0,radius,0);

    int nind = 6*(slices+((stacks-2)*slices));
    MyFile << to_string(nind)+"\n";

    for (int i=1;i<slices+1;i++){
		  if (i==slices){
          MyFile << to_string(1)+"\n";
          MyFile << to_string(0)+"\n";
          MyFile << to_string(i)+"\n";
		  } else {
          MyFile << to_string(i+1)+"\n";
          MyFile << to_string(0)+"\n";
          MyFile << to_string(i)+"\n";
		  }
    }
    for (int i=0;i<(stacks-2);i++){
        for (int j=0;j<slices;j++){
			    if (j==(slices-1)){
                MyFile << to_string((i*slices)+j+1)+"\n";
                MyFile << to_string((i*slices)+slices+j+1)+"\n";
                MyFile << to_string((i*slices)+j+2)+"\n";
                MyFile << to_string((i*slices)+j+2)+"\n";
                MyFile << to_string((i*slices)+1)+"\n";
                MyFile << to_string((i*slices)+j+1)+"\n";
				
			    } else {
                MyFile << to_string((i*slices)+j+1)+"\n";
                MyFile << to_string((i*slices)+slices+j+1)+"\n";
                MyFile << to_string((i*slices)+slices+j+2)+"\n";
                MyFile << to_string((i*slices)+j+2)+"\n";
                MyFile << to_string((i*slices)+j+1)+"\n";
                MyFile << to_string((i*slices)+slices+j+2)+"\n";
			    }
        }
    }
    
    for (int i=2;i<slices+2;i++){
		  if (i==slices+1){
            MyFile << to_string(npoints-i)+"\n";
            MyFile << to_string(npoints-2)+"\n";
            MyFile << to_string(npoints-1)+"\n";
		  } else {
            MyFile << to_string(npoints-i)+"\n";
            MyFile << to_string(npoints-i-1)+"\n";
            MyFile << to_string(npoints-1)+"\n";
		  }
    }
}

void create_cone(float radius,float height,int slices,int stacks,string file){
  ofstream MyFile(file);
  MyFile << "cone\n";
  int npoints = slices*stacks+1;
  MyFile << to_string(npoints+1)+"\n";
	float ang=0,x1=0,y1=0,z1=0,theight=0,tradius=0;
	float alfac = (atan(height/radius));
	float heightinc = height/stacks;
	float radiusdec = heightinc*tan((M_PI/2)-alfac);
	int ia=stacks;
  MyFile << pto_string(0,0,0);
	for (int i=0;i<stacks;i++,ia--){
		theight=i*heightinc;
		tradius=radiusdec*ia;
		for (int j=0;j<slices;j++){
			ang=2*M_PI*((float)j/slices);
			x1=tradius*sin(ang);
			y1=theight;
			z1=tradius*cos(ang);
            MyFile << pto_string(x1,y1,z1);
		}
	}
    MyFile << pto_string(0,height,0);
    int nInd = (slices*6)+((stacks-1)*slices)*6;
    MyFile << to_string(nInd)+"\n";

	for(int i=1;i<slices+1;i++){ 
		if (i==slices){
            MyFile << to_string(1)+"\n";
            MyFile << to_string(i)+"\n";
            MyFile << to_string(0)+"\n";
		} else {
            MyFile << to_string(i+1)+"\n";
            MyFile << to_string(i)+"\n";
            MyFile << to_string(0)+"\n";
		}
	}
	for (int i=0;i<stacks-1;i++){
		for (int j=0;j<slices;j++){
			if (j==(slices-1)){
				if (i==0){

				}
                MyFile << to_string((i*slices)+j+slices+1)+"\n";
                MyFile << to_string((i*slices)+j+1)+"\n";
                MyFile << to_string((i*slices)+j+2)+"\n";

                MyFile << to_string((i*slices)+j+1)+"\n";
                MyFile << to_string((i*slices)+1)+"\n";
                MyFile << to_string((i*slices)+j+2)+"\n";
			} else {

                MyFile << to_string((i*slices)+j+slices+1)+"\n";
                MyFile << to_string((i*slices)+j+1)+"\n";
                MyFile << to_string((i*slices)+j+slices+2)+"\n";

                MyFile << to_string((i*slices)+j+1)+"\n";
                MyFile << to_string((i*slices)+j+2)+"\n";
                MyFile << to_string((i*slices)+j+slices+2)+"\n";
			}
		}
	}

	for(int i=0;i<slices;i++){
		if (i==slices){
            MyFile << to_string(npoints)+"\n";
            MyFile << to_string(npoints-1-slices+i)+"\n";
            MyFile << to_string(npoints-1-slices)+"\n";
		} else {
            MyFile << to_string(npoints)+"\n";
            MyFile << to_string(npoints-1-slices+i)+"\n";
            MyFile << to_string(npoints-slices+i)+"\n";
		}
	}
    MyFile.close();
}

int main(int argc, char const *argv[]) {

  if (argc<2) {
    cout << "O número de argumentos é incorreto. \n\n";

  } else if (strcmp(argv[1], "Plane") == 0) {

      if (argc == 5) {
        float length = stof(argv[2]);
        float width = stof(argv[3]);

        if (length > 0.0f && width > 0.0f) {
          create_plane(length,width,argv[4]);
        }
      }

    } else if (strcmp(argv[1], "Box") == 0) {

        if (argc==6 | argc==7) {
          float length = stof(argv[2]);
          float width = stof(argv[3]);
          float height = stof(argv[4]);
          int divisions = 1;

          if (argc == 7) {
            divisions = stoi(argv[5]);
            if (length > 0.0f && width > 0.0f && height > 0.0f && divisions > 0) {
                //create_box(length, width, height, divisions, argv[6]);

            }
          } else {
            if (length > 0.0f && width > 0.0f && height > 0.0f && divisions > 0) {
              //create_box(length,width,height,divisions,argv[5]);

            }
          }
        }
      } else if (strcmp(argv[1], "Sphere") == 0) {
        float radius=stof(argv[2]);
        int slices=stoi(argv[3]);
        int stacks=stoi(argv[4]);
        if (radius>0.0f&&slices>=0&&stacks>=0) create_sphere(radius,slices,stacks,argv[5]);

    } else if (strcmp(argv[1], "Cone") == 0) {
        float radius=stof(argv[2]);
        float height=stof(argv[3]);
        int slices=stoi(argv[4]);
        int stacks=stoi(argv[5]);
        if (radius>0.0f&&height>0.0f&&slices>=0&&stacks>=0) create_cone(radius,height,slices,stacks,argv[6]);

    } else {
      cout << "Primitiva desconhecida. \n\n";
    }
  return 0;
}
