#include <iostream>
#include <fstream>
#include <string.h>
#include <cstring>
using namespace std;

void create_plane (float length, float width, string file_name) {
  // Create and open a text file
 ofstream MyFile(file_name);

 // Write to the file
 MyFile << "plane\n";
 MyFile << "4\n";

 string point1 = to_string(length/2) + " 0 " + to_string(width/2) + "\n";
 string point2 = to_string(length/2) + " 0 " + to_string(-width/2) + "\n";
 string point3 = to_string(-length/2) + " 0 " + to_string(-width/2) + "\n";
 string point4 = to_string(-length/2) + " 0 " + to_string(width/2) + "\n";

//Escrever pontos no ficheiro
 MyFile << point1;
 MyFile << point2;
 MyFile << point3;
 MyFile << point4;

 // Close the file
 MyFile.close();
}

void create_box (float length, float width, float height, int divisions, string file_name) {
    // Create and open a text file
    ofstream MyFile(file_name);

    // Write to the file
    MyFile << "box\n";
    MyFile << to_string(4 * divisions * divisions * 6) + "\n";

    float translation_l = length / divisions;
    float translation_w = width / divisions;
    float translation_h = height / divisions;

    //Top and base
    for (int k = 0; k < 2; k++) {
        //Na primeira iteração y=height/2, para o topo, e na segunda y=-height/2, para a base.
        float y = (height / 2) - (height * k);

        for (int i = 0; i < divisions; i++) {
            for (int j = 0; j < divisions; j++) {
                //coordenadas do ponto de partida, às quais se aplicarão alterações para obter todos os outros pontos desta face
                float move_x = (translation_l * j) + (-length / 2);
                float move_z = (translation_w * i) + (-width / 2);

                string point1 = to_string(move_x) + " " + to_string(y) + " " + to_string(move_z) + " | ";
                string point2 =to_string(move_x) + " " + to_string(y) + " " + to_string(translation_w + move_z) + " | ";
                string point3 = to_string(translation_l + move_x) + " " + to_string(y) + " " + to_string(translation_w + move_z) + " | ";
                string point4 = to_string(translation_l + move_x) + " " + to_string(y) + " " + to_string(move_z) + "\n";

                //Escrever pontos no ficheiro
                MyFile << point1;
                MyFile << point2;
                MyFile << point3;
                MyFile << point4;
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

                string point1 = to_string(move_x) + " " + to_string(move_y) + " " + to_string(z) + " | ";
                string point2 = to_string(move_x) + " " + to_string(move_y - translation_h) + " " + to_string(z) + " | ";
                string point3 = to_string(move_x + translation_l) + " " + to_string(move_y - translation_h) + " " + to_string(z) + " | ";
                string point4 = to_string(move_x + translation_l) + " " + to_string(move_y) + " " + to_string(z) + "\n";

                //Escrever pontos no ficheiro
                MyFile << point1;
                MyFile << point2;
                MyFile << point3;
                MyFile << point4;
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

                string point1 = to_string(x) + " " + to_string(move_y) + " " + to_string(move_z) + " | ";
                string point2 = to_string(x) + " " + to_string(move_y - translation_h) + " " + to_string(move_z) + " | ";
                string point3 = to_string(x) + " " + to_string(move_y - translation_h) + " " + to_string(move_z - translation_w) + " | ";
                string point4 = to_string(x) + " " + to_string(move_y) + " " + to_string(move_z - translation_w) + "\n";

                //Escrever pontos no ficheiro
                MyFile << point1;
                MyFile << point2;
                MyFile << point3;
                MyFile << point4;
            }
        }
    }

    MyFile.close();

}




int main(int argc, char const *argv[]) {

  if (argc<2) {
    cout << "O número de argumentos é incorreto. \n\n";

  } else {

    if (strcmp(argv[1], "Plane") == 0) {

      if (argc == 5) {
        float length = stof(argv[2]);
        float width = stof(argv[3]);

        if (length > 0.0f && width > 0.0f) {
          create_plane(length,width,argv[4]);
        }
      }

    } else if (strcmp(argv[1], "Box") == 0) {

        if (argc >= 6) {
          float length = stof(argv[2]);
          float width = stof(argv[3]);
          float height = stof(argv[4]);
          int divisions = 1;

          if (argc == 7) {
            divisions = stoi(argv[5]);
            if (length > 0.0f && width > 0.0f && height > 0.0f && divisions > 0) {
              create_box(length,width,height,divisions,argv[6]);

          } else {
            if (length > 0.0f && width > 0.0f && height > 0.0f && divisions > 0) {
              create_box(length,width,height,divisions,argv[5]);
            }
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

  }


  return 0;
}
