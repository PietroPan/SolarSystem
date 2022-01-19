#include "plane.h"

void create_plane (float length, float width, string file_name) {
  // Create and open a text file
 ofstream MyFile(file_name);

 // Write to the file
 MyFile << "plane\n";
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

 //Numero de indices
 MyFile << "6\n";

 MyFile << "0\n";
 MyFile << "1\n";
 MyFile << "2\n";
 MyFile << "2\n";
 MyFile << "3\n";
 MyFile << "0\n";

 MyFile << "0 1 0\n";
 MyFile << "0 1 0\n";
 MyFile << "0 1 0\n";
 MyFile << "0 1 0\n";

 MyFile << "1 1\n";
 MyFile << "1 0\n";
 MyFile << "0 0\n";
 MyFile << "0 1\n";

 // Close the file
 MyFile.close();
}