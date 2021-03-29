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
#include <map>
#include "drawable.h"

using namespace std;

class Figura3d: public Drawable {

private:
    int nr_pontos;
    float** pontos;


    void file2figure(ifstream &file) {
        if (file.is_open()) {
            char contentor[100];
            string tipoFigura;
            getline(file, tipoFigura); // Ignora a primeira linha, que indica o tipo de figura

            file.getline(contentor, 100); // contentor tem o número de pontos distinctos (em caracteres)
            int distinctPoints = stoi(contentor);

            float arrayAuxiliar[distinctPoints][3];

            for (int i = 0; i < distinctPoints; i++) {
                file.getline(contentor, 99);
                int index = 0;
                for (int x = 0; x<3; x++) {
                    char umFloat[50];
                    for (int n = 0; contentor[index] != ' ' && contentor[index] != '\0'; n++, index++) {
                        umFloat[n] = contentor[index];
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
            file2figure(infile);
        }
        infile.close();
    }


    void draw() {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBegin(GL_TRIANGLES);
        glColor3f(42.f/255.f,157.f/255.f,143.f/255.f);

        for (int i = 0; i < this->nr_pontos; i++) {
            glVertex3f(pontos[i][0], pontos[i][1], pontos[i][2]);
        }
        glEnd();
    }
};