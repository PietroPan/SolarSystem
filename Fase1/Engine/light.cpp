#include "gereIncludes.h"
#include "drawable.h"

class Light: public Drawable {
private:
    int n;
    float ambC[4]={0.2,0.2,0.2,1};
    float diffC[4]={1,1,1,1};
    float specC[4]={1,1,1,1};
    float pos[4]={1,1,1,1};
    float dir[4]={1,1,1,0};
    float cutOff=180.0f; float exponent=64.0f;
    bool isDir=false; bool isPoint=false; bool isSpot=false;
    bool amb=false; bool diff=false; bool spec=false;
    bool isDefault;
public:
    Light(){}
    void initLight(int number,string type){
        if (type=="DIRECTIONAL"){
            isDir = true;
        } else if (type=="SPOT"){
            isSpot = true;
        } else if (type=="POINT"){
            isPoint = true;
        }
        n=number;
    }

    void setAmbR(float ambR){
        this->ambC[0]=ambR;
    }
    void setAmbG(float ambG){
        this->ambC[1]=ambG;
    }
    void setAmbB(float ambB){
        this->ambC[2]=ambB;
    }
    void setDiffR(float diffR){
        this->diffC[0]=diffR;
    }
    void setDiffG(float diffG){
        this->diffC[1]=diffG;
    }
    void setDiffB(float diffB){
        this->diffC[2]=diffB;
    }
    void setSpecR(float specR){
        this->specC[0]=specR;
    }
    void setSpecG(float specG){
        this->specC[1]=specG;
    }
    void setSpecB(float specB){
        this->specC[2]=specB;
    }
    void setCutOff(float cutOff){
        this->cutOff=cutOff;
    }
    void setExponent(float exponent){
        this->exponent=exponent;
    }
    void hasAmb(){
        this->amb=true;
    }
    void hasDiff(){
        this->diff=true;
    }
    void hasSpec(){
        this->spec=true;
    }
    void notDefault(){
        this->isDefault=false;
    }

    void setPosX(float x){
        this->pos[0]=x;
    }
    void setPosY(float y){
        this->pos[1]=y;
    }
    void setPosZ(float z){
        this->pos[2]=z;
    }

    void setDirX(float x){
        this->dir[0]=x;
    }
    void setDirY(float y){
        this->dir[1]=y;
    }
    void setDirZ(float z){
        this->dir[2]=z;
    }
    
    void setUp(){
        glEnable(GL_LIGHT0+n);
        if (isDefault){
            glLightfv(GL_LIGHT0+n,GL_AMBIENT,ambC);
            glLightfv(GL_LIGHT0+n,GL_DIFFUSE,diffC);
            glLightfv(GL_LIGHT0+n,GL_SPECULAR,specC);
        } else {
            if (amb){
                glLightfv(GL_LIGHT0+n,GL_AMBIENT,ambC);
            }
            if (diff){
                glLightfv(GL_LIGHT0+n,GL_DIFFUSE,diffC);
            }
            if (spec){
                glLightfv(GL_LIGHT0+n,GL_SPECULAR,specC);
            }
        }
    }

    void draw(){
        if (isDir){
            glLightfv(GL_LIGHT0+n,GL_POSITION,dir);
        } else if (isPoint){
            glLightfv(GL_LIGHT0+n,GL_POSITION,pos);
        } else if (isSpot){
            glLightfv(GL_LIGHT0+n,GL_POSITION,pos);
            glLightfv(GL_LIGHT0+n,GL_SPOT_DIRECTION,dir);
            glLightf(GL_LIGHT0+n,GL_SPOT_CUTOFF,cutOff);
            glLightf(GL_LIGHT0+n,GL_SPOT_EXPONENT,exponent);
        }
    }
};
