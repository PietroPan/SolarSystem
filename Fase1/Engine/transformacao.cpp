//
// Created by mane on 29/03/21.
//
#include "gereIncludes.h"
#include "drawable.h"

extern int oldTimeSinceStart;
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
    float x,y,z,time;
    bool rotating;

public:
    Rotacao(int ang, float time, float x, float y, float z,bool rotating) {
        this->angulo = ang;
        this->time = time;
        this->x = x;
        this->y = y;
        this->z = z;
        this->rotating=rotating;
    }

    void draw() {
        if (rotating){
            int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
            float trueTime = ((float)timeSinceStart/1000.0f);
            if (time>0){
                glRotatef(trueTime*360.0f/time,x,y,z);
            }
        } else {
            glRotatef(angulo, x, y, z);
        }
        
        //float deltaTime = (float)(timeSinceStart - oldTimeSinceStart)/1000.0f;
        //oldTimeSinceStart = timeSinceStart;
        //glRotatef(angulo, x, y, z);
        //glRotatef(deltaTime*360/angulo,x,y,z);
        //glRotatef(trueTime*360.0f/(float)angulo,x,y,z);
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
