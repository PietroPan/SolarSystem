//
// Created by mane on 29/03/21.
//
#include "gereIncludes.h"
#include "drawable.h"
#include "catmullRomCurve.h"

extern bool drawCurves;
class Transformacao: public Drawable {};

// translacao
class Translacao: public Transformacao {
private:
    float x, y, z, time;
    vector<vector<float>> points;
    float yAxis[3]={0,-1,0}; 
    bool curve;

public:
    Translacao() {
        x = y = z = 0.0f;
    }

    Translacao(float x, float y, float z,vector<vector<float>> points,bool curve,float time) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->time = time;
        this->points = points;
        this->curve = curve;
    }


    void draw() {
        if (this->curve){
            if (drawCurves) renderCatmullRomCurve(this->points);
            catmullRomTranslate(this->time,this->points,this->yAxis);
        } else
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
        if (this->rotating){
            int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
            float trueTime = ((float)timeSinceStart/1000.0f);
            if (time>0){
                glRotatef(trueTime*360.0f/time,x,y,z);
            }
        } else {
            glRotatef(angulo, x, y, z);
        }
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
