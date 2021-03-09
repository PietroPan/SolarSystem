
#include <iostream>
#include <fstream>
using namespace std;


int main(int argc, char const *argv[]) {

  if (argc<2) {
    cout << "O número de argumentos é incorreto. \n\n";

  } else {

    if (strcmp(argv[1], "Plane") == 0) {
      //do something

    } else if (strcmp(argv[1], "Box") == 0) {
      //do something

    } else if (strcmp(argv[1], "Sphere") == 0) {
      //do something

    } else if (strcmp(argv[1], "Cone") == 0) {
      //do something

    } else {
      cout << "Primitiva desconhecida. \n\n"
    }

  }

  return 0;
}
