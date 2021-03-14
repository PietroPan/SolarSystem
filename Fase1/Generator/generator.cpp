#include "generator.h"

string pto_string(float x,float y,float z){
    return to_string(x)+" "+to_string(y)+" "+to_string(z)+"\n";
}

int main(int argc, char **argv) {

  if (argc<2) {
    cout << "O número de argumentos é incorreto. \n\n";

  } else if (strcmp(argv[1], "plane") == 0) {

      if (argc == 5) {
        float length = stof(argv[2]);
        float width = stof(argv[3]);

        if (length > 0.0f && width > 0.0f) {
          create_plane(length,width,argv[4]);
        }
      }

    } else if (strcmp(argv[1], "box") == 0) {

        if (argc==6 | argc==7) {
          float length = stof(argv[2]);
          float width = stof(argv[3]);
          float height = stof(argv[4]);
          int divisions = 1;

          if (argc == 7) {
            divisions = stoi(argv[5]);
            if (length > 0.0f && width > 0.0f && height > 0.0f && divisions > 0) {
                pointsBox(length,width,height,divisions,argv[6]);
            }
          } else {
            if (length > 0.0f && width > 0.0f && height > 0.0f && divisions > 0) {
            }
          }
        }
      } else if (strcmp(argv[1], "sphere") == 0) {
        float radius=stof(argv[2]);
        int slices=stoi(argv[3]);
        int stacks=stoi(argv[4]);
        if (radius>0.0f&&slices>=0&&stacks>=0) pointsSphere(radius,slices,stacks,argv[5]);

    } else if (strcmp(argv[1], "cone") == 0) {
        float radius=stof(argv[2]);
        float height=stof(argv[3]);
        int slices=stoi(argv[4]);
        int stacks=stoi(argv[5]);
        if (radius>0.0f&&height>0.0f&&slices>=0&&stacks>=0) pointsCone(radius,height,slices,stacks,argv[6]);
    } else {
      cout << "Primitiva desconhecida. \n\n";
    }
  return 0;
}
