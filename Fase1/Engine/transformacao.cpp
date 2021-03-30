//
// Created by mane on 29/03/21.
//
#include "gereIncludes.h"
#include "drawable.h"

class Transformacao: public Drawable {};

// translacao
class Translacao: public Transformacao {
private:
    float x, y, z;

public:
    Translacao() {
        x = y = z = 0.0f;
    }

    Translacao(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void draw() {
        glTranslatef(x, y, z);
    }
};

// rotacao
class Rotacao: public Transformacao {
private:
    int angulo;
    float x,y,z;

public:
    Rotacao(int ang, float x, float y, float z) {
        this->angulo = ang;
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void draw() {
        glRotatef(angulo, x, y, z);
    }
};

// escala
class Escala: public Transformacao {
private:
    float x, y, z;
public:
    Escala(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void draw() {
        glScalef(x,y,z);
    }
};
