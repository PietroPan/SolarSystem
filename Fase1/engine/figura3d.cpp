#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <iterator>
#include <cstring>

using namespace std;

#define HEIGHT 2.0f

class Figura3d {

private:
    int nr_pontos;
    float** pontos;

    void readPlane(ifstream &file) {
        if (file.is_open()) {
            char contentor[100];
            file.getline(contentor, 100);
            this->nr_pontos = stoi(contentor);
            //cout << "Vai ler " << this->nr_pontos << " pontos" << endl;
            this->pontos = new float*[nr_pontos];
            for (int i = 0; i<nr_pontos; i++) {
                file.getline(contentor, 100);
                float coordsPonto[3];
                int index = 1;
                for (int x = 0; x<3; x++) {
                    char umFloat[50];
                    for (int n = 0; contentor[index] != ',' && contentor[index] != ')'; n++) {
                        umFloat[n] = contentor[index++];
                        umFloat[n+1] = '\0';
                    }
                    index++;
                    coordsPonto[x] = stof(umFloat);
                }
                (this->pontos)[i] = new float[3];
                for (int n = 0; n<3; n++) {
                    (this->pontos)[i][n] = coordsPonto[n];
                }
            }
        }
    }

    void readBox() {}

    void readSphere(ifstream &file) {
        if (file.is_open()) {
            char contentor[100];
            int distinctPoints;
            file.getline(contentor, 100); // contentor tem o número de pontos distinctos (em caracteres)

            distinctPoints = stoi(contentor);
            float arrayAuxiliar[distinctPoints][3];

            for (int i = 0; i < distinctPoints; i++) {
                file.getline(contentor, 100);
                float coordsPonto[3];
                int index = 0;
                for (int x = 0; x<3; x++) {
                    char umFloat[50];
                    for (int n = 0; contentor[index] != ' ' && contentor[index] != '\n'; n++) {
                        umFloat[n] = contentor[index++];
                        umFloat[n+1] = '\0';
                    }
                    index++;
                    arrayAuxiliar[i][x] = stof(umFloat);
                }
            }

            file.getline(contentor, 100); // contentor tem o número de pontos para desenhar
            this->nr_pontos = stoi(contentor);

            this->pontos = new float*[nr_pontos];
            for (int i = 0; i < nr_pontos; i++) {
                (this->pontos)[i] = new float[3];
                file.getline(contentor, 20);
                int indice = stoi(contentor);

                for (int n = 0; n < 3; n++) {
                    this->pontos[i][n] = arrayAuxiliar[indice][n];
                }
            }
        }
    }

public:

    Figura3d(string nomeFicheiro) {
        ifstream infile(nomeFicheiro.c_str());
        if (infile.is_open()) {
            char tipoFigura[50];
            infile.getline(tipoFigura, 50);

            if (strcmp(tipoFigura, "plane") == 0) readPlane(infile);
            else if (strcmp(tipoFigura, "sphere") == 0 || strcmp(tipoFigura, "cone") == 0) readSphere(infile);
        }

        infile.close();
    }



    void draw() {
        glBegin(GL_TRIANGLES);
        int aux = nr_pontos / 3;

        for (int i = 0; i<aux; i++) {
            glColor3f(static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
                      static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
                      static_cast <float> (rand()) / static_cast <float> (RAND_MAX));

            for (int j = 0; j<3; j++) {
                int pos = 3 * i + j;
                glVertex3f(pontos[pos][0], pontos[pos][1], pontos[pos][2]);
            }
        }
        glEnd();
    }
};