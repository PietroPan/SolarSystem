#include "generator.h"

string pto_string(float x,float y,float z){
    return to_string(x)+" "+to_string(y)+" "+to_string(z)+"\n";
}

int main(int argc, char **argv) {

  ilInit();

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

        if (argc==6 | argc==7 | argc==8) {
          float length = stof(argv[2]);
          float width = stof(argv[3]);
          float height = stof(argv[4]);
          int divisions = 1;

          if (argc == 7) {
            divisions = stoi(argv[5]);
            if (length > 0.0f && width > 0.0f && height > 0.0f && divisions > 0) {
                pointsBox(length,width,height,divisions,argv[6],false,false);
            }
          } else if (argc == 8) {
            divisions = stoi(argv[5]);
            if (length > 0.0f && width > 0.0f && height > 0.0f && divisions > 0) {
              cout << argv[6];
              if (strcmp(argv[6], "rep") == 0) pointsBox(length,width,height,divisions,argv[7],false,true);
              else pointsBox(length,width,height,divisions,argv[7],false,false);
            }
          }
        }
      } else if (strcmp(argv[1], "invertedBox") == 0) {

        if (argc==6 | argc==7 | argc==8) {
          float length = stof(argv[2]);
          float width = stof(argv[3]);
          float height = stof(argv[4]);
          int divisions = 1;

          if (argc == 7) {
            divisions = stoi(argv[5]);
            if (length > 0.0f && width > 0.0f && height > 0.0f && divisions > 0) {
                pointsBox(length,width,height,divisions,argv[6],true,false);
            }
          } else if (argc == 8) {
            divisions = stoi(argv[5]);
            if (length > 0.0f && width > 0.0f && height > 0.0f && divisions > 0) {
              if (strcmp(argv[6], "rep") == 0) pointsBox(length,width,height,divisions,argv[7],true,true);
              else pointsBox(length,width,height,divisions,argv[7],true,false);
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
    } else if (strcmp(argv[1], "cilinder") == 0) {
        float radius=stof(argv[2]);
        float height=stof(argv[3]);
        int slices=stoi(argv[4]);
        int stacks=stoi(argv[5]);
        if (radius>0.0f&&height>0.0f&&slices>=0&&stacks>=0) pointsCilinder(radius,height,slices,stacks,argv[6]);
    } else if (strcmp(argv[1], "torus") == 0) {
        float inRadius=stof(argv[2]);
        float outRadius=stof(argv[3]);
        int rings=stoi(argv[4]);
        int sides=stoi(argv[5]);
        if (inRadius>0.0f&&outRadius>0.0f&&sides>=0&&rings>=0) pointsTorus(inRadius,outRadius,sides,rings,argv[6]);
    } else if (strcmp(argv[1],"bezierPatch") == 0) {
        int tess=stoi(argv[3]);
        pointsBezier(argv[2],tess,argv[4]);
    } else if (strcmp(argv[1],"terrain") == 0) {
        pointsTerrain(argv[2],argv[4],stof(argv[3]));
    } else {
      cout << "Primitiva desconhecida. \n\n";
    }
  return 0;
}
