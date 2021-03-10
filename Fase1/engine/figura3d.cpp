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
using namespace std;

#define HEIGHT 2.0f

class Figura3d {
protected:
    int nr_pontos;
    float** pontos;

    Figura3d(int nr = 0, float arrayPontos[][3] = nullptr) {
        nr_pontos = nr;
        pontos = new float*[nr];
        for (int l = 0; l<nr; l++) {
            pontos[l] = new float[3];
            for (int c = 0; c<3; c++) {
                pontos[l][c] = arrayPontos[l][c];
            }
        }
    }

public:

    virtual void draw() = 0;
};

class Plano : public Figura3d {
public:

    Plano(int nr, float arrayPontos[][3]): Figura3d(nr, arrayPontos){}

    Plano(ifstream &file) {
        if (file.is_open()) {
            char contentor[100];
            file.getline(contentor, 100);
            this->nr_pontos = stoi(contentor);
            cout << "Vai ler " << this->nr_pontos << " pontos" << endl;
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

    void draw() {
        glColor3f(0.0f, 1.0f,0.5);

        glBegin(GL_TRIANGLES);
        for (int l = 0; l<nr_pontos; l++) {
            cout << "Põe vértice" << endl;
            glVertex3f(pontos[l][0], pontos[l][1], pontos[l][2]);
        }
        glEnd();
        cout << "Acaba de desenhar";
    }
};