#include <iostream>
#include <fstream>
#include <cstring>
#include <map>
#include <math.h>
#include <limits>
using namespace std;

float limit_float (float f, int n) {
  /* float val = 37.777779;

  float rounded_down = floorf(val * 100) / 100;   Result: 37.77
  float nearest = roundf(val * 100) / 100;        Result: 37.78
  float rounded_up = ceilf(val * 100) / 100;      Result: 37.78

  */
  return roundf(f * pow(10,n)) / pow(10,n);
}

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
    return index; //retorna o mesmo valor de index passado como argumento para indicar que não houve inserção no mapa
  }

}

void create_box (float length, float width, float height, int divisions, string file_name) {
    // Create and open a text file
    ofstream MyFile(file_name);

    // Write to the file
    MyFile << "Box\n";
    MyFile << to_string(4 * divisions * divisions * 6) + "\n"; //ns se esta bem

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
      //do something

    } else if (strcmp(argv[1], "Cone") == 0) {
      //do something

    } else {
      cout << "Primitiva desconhecida. \n\n";
    }
  return 0;
}
