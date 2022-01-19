#include "gereIncludes.h"
#include "drawable.h"

class Material: public Drawable {
private:
    float ambC[4]={1,1,1,1};
    float diffC[4]={1,1,1,1};
    float specC[4]={1,1,1,1};
    float emissC[4]={1,1,1,1};
    int shineI=128;
    bool amb=false; bool diff=false;
    bool spec=false; bool shine=false;
    bool emiss=false;
public:
    Material(){}

    void setAmbR(float ambR){
        this->ambC[0]=ambR;
        hasAmb();
    }
    void setAmbG(float ambG){
        this->ambC[1]=ambG;
        hasAmb();
    }
    void setAmbB(float ambB){
        this->ambC[2]=ambB;
        hasAmb();
    }
    void setDiffR(float diffR){
        this->diffC[0]=diffR;
        hasDiff();
    }
    void setDiffG(float diffG){
        this->diffC[1]=diffG;
        hasDiff();
    }
    void setDiffB(float diffB){
        this->diffC[2]=diffB;
        hasDiff();
    }
    void setSpecR(float specR){
        this->specC[0]=specR;
        hasSpec();
    }
    void setSpecG(float specG){
        this->specC[1]=specG;
        hasSpec();
    }
    void setSpecB(float specB){
        this->specC[2]=specB;
        hasSpec();
    }

    void setEmissR(float emissR){
        this->emissC[0]=emissR;
        hasEmiss();
    }
    void setEmissG(float emissG){
        this->emissC[1]=emissG;
        hasEmiss();
    }
    void setEmissB(float emissB){
        this->emissC[2]=emissB;
        hasEmiss();
    }

    void setShineI(int shineI){
        this->shineI=shineI;
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
    void hasEmiss(){
        this->emiss=true;
    }

    void draw(){
        glPushAttrib(GL_LIGHTING_BIT);
        if (amb){
            glMaterialfv(GL_FRONT,GL_AMBIENT,ambC);
        }
        if (diff){
            glMaterialfv(GL_FRONT,GL_SPECULAR,diffC);
        }
        if (spec){
            glMaterialfv(GL_FRONT,GL_DIFFUSE,specC);
        }
        if (emiss){
            glMaterialfv(GL_FRONT,GL_EMISSION,emissC);
        }
        glMaterialf(GL_FRONT,GL_SHININESS,shineI);
    }
};