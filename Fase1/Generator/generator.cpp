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


int search_point(ostream& file, map<string,int>& m, string point, int index) {
  auto it = m.find(point);
  if ( it == m.end() ) {
    m.insert({point,index});
    file << point;
    return index+1; //retorna o valor de index incrementado para indicar que houve inserção no mapa

  } else {
    // found
    file << "i" + to_string(it->second) + "\n";
    return it->second; //retorna o valor de index que indica o indice em que estava o ponto
  }

}



void create_box (float length, float width, float height, int divisions, string file_name) {
    // Create and open a text file
    ofstream MyFile(file_name);

    // Write to the file
    MyFile << "Box\n";
    MyFile << to_string(6 * divisions * divisions * 6) + "\n"; //ns se esta bem

    float translation_l = length / divisions;
    float translation_w = width / divisions;
    float translation_h = height / divisions;

    map<string,int> m;

    int index = 0;
    std::cout.precision(std::numeric_limits<float>::digits10);

    //Top and base
    for (int k = 0; k < 2; k++) {
        //Na primeira iteração y=height/2, para o topo, e na segunda y=-height/2, para a base.
        float y = (height / 2) - (height * k);

        for (int i = 0; i < divisions; i++) {
            for (int j = 0; j < divisions; j++) {

                //coordenadas do ponto de partida, às quais se aplicarão alterações para obter todos os outros pontos desta face
                float move_x = (translation_l * j) + (-length / 2);
                float move_z = (translation_w * i) + (-width / 2);
                int index_point0;
                int index_point2;

                string point0 = to_string(move_x) + " " + to_string(y) + " " + to_string(move_z) + "\n";
                index_point0 = search_point(MyFile, m, point0, index);
                if (index_point0 > index) { index = index_point0; index_point0--; }

                string point1 =to_string(move_x) + " " + to_string(y) + " " + to_string(translation_w + move_z) + "\n";
                int res = search_point(MyFile,m,point1,index);
                if (res > index) index = res;

                string point2 = to_string(translation_l + move_x) + " " + to_string(y) + " " + to_string(translation_w + move_z) + "\n";
                index_point2 = search_point(MyFile, m, point2, index);
                if (index_point2 > index) { index = index_point2; index_point2--; }

                //Segundo triangulo
                MyFile << "i" + to_string(index_point2) + "\n";

                string point3 = to_string(translation_l + move_x) + " " + to_string(y) + " " + to_string(move_z) + "\n";
                res = search_point(MyFile, m, point3, index);
                if (res > index) index = res;

                MyFile << "i" + to_string(index_point0) + "\n";


            }
        }
    }

    //Front and back
    for (int k = 0; k < 2; k++) {
        //Na primeira iteração z=width/2, para a face da frente, e na segunda z=-width/2, para a face trás.
        float z = (width / 2) - (width * k);

        for (int i = 0; i < divisions; i++) {
            for (int j = 0; j < divisions; j++) {
                //coordenadas do ponto de partida, às quais se aplicarão alterações para obter todos os outros pontos desta face
                float move_x = (translation_l * j) + (-length / 2);
                float move_y = (height / 2) - (translation_h * i);
                int index_point0;
                int index_point2;

                string point0 = to_string(move_x) + " " + to_string(move_y) + " " + to_string(z) + "\n";
                index_point0 = search_point(MyFile, m, point0, index);
                if (index_point0 > index) { index = index_point0; index_point0--; }

                string point1 = to_string(move_x) + " " + to_string(move_y - translation_h) + " " + to_string(z) + "\n";
                int res = search_point(MyFile,m,point1,index);
                if (res > index) index = res;

                string point2 = to_string(move_x + translation_l) + " " + to_string(move_y - translation_h) + " " + to_string(z) + "\n";
                index_point2 = search_point(MyFile, m, point2, index);
                if (index_point2 > index) { index = index_point2; index_point2--; }

                //Segundo triangulo
                MyFile << "i" + to_string(index_point2) + "\n";

                string point3 = to_string(move_x + translation_l) + " " + to_string(move_y) + " " + to_string(z) + "\n";
                res = search_point(MyFile, m, point3, index);
                if (res > index) index = res;

                MyFile << "i" + to_string(index_point0) + "\n";

            }
        }
    }


    //Right and left
    for (int k = 0; k < 2; k++) {
        //Na primeira iteração x=length/2, para a face da direita, e na segunda x=-length/2, para a face da esquerda.
        float x = (length / 2) - (length * k);

        for (int i = 0; i < divisions; i++) {
            for (int j = 0; j < divisions; j++) {
                //coordenadas do ponto de partida, às quais se aplicarão alterações para obter todos os outros pontos desta face
                float move_y = (height / 2) - (translation_h * i);
                float move_z = (width / 2) - (translation_w * j);
                int index_point0;
                int index_point2;

                string point0 = to_string(x) + " " + to_string(move_y) + " " + to_string(move_z) + "\n";
                index_point0 = search_point(MyFile, m, point0, index);
                if (index_point0 > index) { index = index_point0; index_point0--; }

                string point1 = to_string(x) + " " + to_string(move_y - translation_h) + " " + to_string(move_z) + "\n";
                int res = search_point(MyFile,m,point1,index);
                if (res > index) index = res;

                string point2 = to_string(x) + " " + to_string(move_y - translation_h) + " " + to_string(move_z - translation_w) + "\n";
                index_point2 = search_point(MyFile, m, point2, index);
                if (index_point2 > index) { index = index_point2; index_point2--; }

                //Segundo triangulo
                MyFile << "i" + to_string(index_point2) + "\n";

                string point3 = to_string(x) + " " + to_string(move_y) + " " + to_string(move_z - translation_w) + "\n";
                res = search_point(MyFile, m, point3, index);
                if (res > index) index = res;

                MyFile << "i" + to_string(index_point0) + "\n";

            }
        }
    }

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
                create_box(length, width, height, divisions, argv[6]);
                /*
                string point0 = to_string(0.2f) + " " + to_string(1.5f) + " " + to_string(0.7f) + "\n";
                string point1 = to_string(0.2f) + " " + to_string(1.5f) + " " + to_string(0.7f) + "\n";
                cout << to_string(point0.compare(point1)) + "\n";
                */

            }
          } else {
            if (length > 0.0f && width > 0.0f && height > 0.0f && divisions > 0) {
              create_box(length,width,height,divisions,argv[5]);

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
