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

 string ponto1 = to_string(length/2) + " 0 " + to_string(width/2) + "\n";
 string ponto2 = to_string(length/2) + " 0 " + to_string(-width/2) + "\n";
 string ponto3 = to_string(-length/2) + " 0 " + to_string(-width/2) + "\n";
 string ponto4 = to_string(-length/2) + " 0 " + to_string(width/2) + "\n";

 MyFile << ponto1;
 MyFile << ponto2;
 MyFile << ponto3;
 MyFile << ponto4;

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
        //Na primeira iteração y=height/2, para o topo, e na segunda y=-height/2. para a base.
        float y = (height / 2) - (height * k);

        for (int i = 0; i < divisions; i++) {
            for (int j = 0; j < divisions; j++) {
                float move_x = (translation_l * j) + (-length / 2);
                float move_z = (translation_w * i) + (-width / 2);
                string point1 = to_string(move_x) + " " + to_string(y) + " " + to_string(move_z) + " | ";
                string point2 =to_string(move_x) + " " + to_string(y) + " " + to_string(translation_w + move_z) + " | ";
                string point3 = to_string(translation_l + move_x) + " " + to_string(y) + " " + to_string(translation_w + move_z) + " | ";
                string point4 = to_string(translation_l + move_x) + " " + to_string(y) + " " + to_string(move_z) + "\n";
                //por pontos no file
                MyFile << ponto1;
                MyFile << ponto2;
                MyFile << ponto3;
                MyFile << ponto4;
            }
        }
    }

    //Front and back
    for (int k = 0; k < 2; k++) {
        //Na primeira iteração z=width/2, para a frente, e na segunda z=-width/2, para trás.
        float z = (width / 2) - (width * k);

        for (int i = 0; i < divisions; i++) {
            for (int j = 0; j < divisions; j++) {
                float move_x = (translation_l * j) + (-length / 2);
                float move_y = (height / 2) - (translation_h * i);
                string point1 = to_string(move_x) + " " + to_string(move_y) + " " + to_string(z) + " | ";
                string point2 = to_string(move_x) + " " + to_string(move_y - translation_h) + " " + to_string(z) + " | ";
                string point3 = to_string(move_x + translation_l) + " " + to_string(move_y - translation_h) + " " + to_string(z) + " | ";
                string point4 = to_string(move_x + translation_l) + " " + to_string(move_y) + " " + to_string(z) + "\n";
                //por pontos no file
                MyFile << ponto1;
                MyFile << ponto2;
                MyFile << ponto3;
                MyFile << ponto4;
            }
        }
    }


    //Right and left
    

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
