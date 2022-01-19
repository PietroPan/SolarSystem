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
    float yAxis[3]={0,1,0}; 
    bool curve;
    float oldTime=0.0f;
    float h=0.0f;

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
            float newTime = glutGet(GLUT_ELAPSED_TIME);
            float deltaTime = (newTime - this->oldTime)/1000.0f;
            this->oldTime = newTime;
            (this->h)+=deltaTime/(this->time);

            if (drawCurves) renderCatmullRomCurve(this->points);
            catmullRomTranslate(this->h,this->points,this->yAxis);
        } else
        glTranslatef(x, y, z);
    }
};

// rotacao
class Rotacao: public Transformacao {
private:
    float angulo;
    float x,y,z,time;
    bool rotating;
    float oldTime=0.0f;

public:
    Rotacao(float ang, float time, float x, float y, float z,bool rotating) {
        this->angulo = ang;
        this->time = time;
        this->x = x;
        this->y = y;
        this->z = z;
        this->rotating=rotating;
    }

    void draw() {
        if (this->rotating){
            float newTime = glutGet(GLUT_ELAPSED_TIME);
            float deltaTime = (newTime - this->oldTime)/1000.0f;
            this->oldTime = newTime;
            
            if (time>0){
                (this->angulo)+=(deltaTime*360.0f/time);
                glRotatef(this->angulo,x,y,z);
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


