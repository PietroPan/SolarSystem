#include "gereIncludes.h"
#include "drawable.h"

class Texture: public Drawable {
private:
    string texture;
    GLuint id;
    unsigned int t,tw,th;
    unsigned char *texData;
    unsigned int texID;
public:
    Texture(string tex){
        ilInit();
        ilEnable(IL_ORIGIN_SET);
        ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
        ilGenImages(1,&t);
        ilBindImage(t);
        ilLoadImage((ILstring)tex.c_str());
        tw = ilGetInteger(IL_IMAGE_WIDTH);
        th = ilGetInteger(IL_IMAGE_HEIGHT);
        ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
        texData = ilGetData();

        glGenTextures(1,&texID);
        glBindTexture(GL_TEXTURE_2D,texID);
        
        glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
        glGenerateMipmap(GL_TEXTURE_2D);

        this->id=texID;
    }

    void draw(){
        glBindTexture(GL_TEXTURE_2D,this->id);
    }
};
