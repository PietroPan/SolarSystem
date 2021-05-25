#include "gereIncludes.h"
#include "drawable.h"

class Figura3d: public Drawable {

private:
    //int nr_pontos;
    //float** pontos;
    //unsigned int pointsCount;
    unsigned int indexsCount;
    GLuint vertices, indices, normals, texCoords;
    bool isTerrain=false;
    int w,h;


    void processTerrain(ifstream &file){
        this->isTerrain=true;
        vector<float> points;
        string s;
        //getline(file, s); // Ignora a primeira linha, que indica o tipo de figura
        getline(file, s);
        w=stoi(s);
        getline(file, s); 
        h=stoi(s);
        char contentor[100];

        int distinctPoints = (w*2*h);
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
                //arrayAuxiliar[i][x] = stof(umFloat);
                points.push_back(stof(umFloat));
            }
        }

        this->indexsCount=points.size();

        glGenBuffers(1, &this->vertices);
        glBindBuffer(GL_ARRAY_BUFFER,this->vertices);
        glBufferData(GL_ARRAY_BUFFER,sizeof(float)*points.size(),points.data(),GL_STATIC_DRAW);
    }
    
    
void file2figure(ifstream &file) {
    if (file.is_open()) {
        string tipoFigura;
        getline(file, tipoFigura); // Ignora a primeira linha, que indica o tipo de figura
        if (tipoFigura=="terrain"){

            processTerrain(file);

        } else {
            vector<unsigned int> indexs;
            vector<float> points;
            vector<float> n;
            vector<float> t;

            char contentor[100];

            file.getline(contentor, 100); // contentor tem o número de pontos distinctos (em caracteres)
            int distinctPoints = stoi(contentor);

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
                    points.push_back(stof(umFloat));
                }
            }

            file.getline(contentor, 100); // contentor tem o número de pontos para desenhar
            this->indexsCount = stoi(contentor);

            for (int i = 0; i < this->indexsCount; i++) {
                file.getline(contentor, 20);
                int indice = stoi(contentor);
                indexs.push_back(indice);
            }

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
                    n.push_back(stof(umFloat));
                }
            }
            

            for (int i = 0; i < distinctPoints; i++) {
                file.getline(contentor, 99);
                int index = 0;
                for (int x = 0; x<2; x++) {
                    char umFloat[50];
                    for (int n = 0; contentor[index] != ' ' && contentor[index] != '\0'; n++, index++) {
                        umFloat[n] = contentor[index];
                        umFloat[n+1] = '\0';
                    }
                    index++;
                    
                    t.push_back(stof(umFloat));
                }
            }

            glGenBuffers(1, &this->vertices);
            glBindBuffer(GL_ARRAY_BUFFER,this->vertices);
            glBufferData(GL_ARRAY_BUFFER,sizeof(float)*points.size(),points.data(),GL_STATIC_DRAW);

            glGenBuffers(1, &(this->indices));
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,this->indices);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*indexs.size(),indexs.data(),GL_STATIC_DRAW);


            glGenBuffers(1, &(this->normals));
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,this->normals);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(float)*n.size(),n.data(),GL_STATIC_DRAW);

            glGenBuffers(1, &(this->texCoords));
            glBindBuffer(GL_ARRAY_BUFFER,this->texCoords);
            glBufferData(GL_ARRAY_BUFFER, t.size() * sizeof(float), t.data(), GL_STATIC_DRAW);

   
        }
    }
}

public:

    Figura3d(string nomeFicheiro) {
        ifstream infile(nomeFicheiro.c_str());
        bool b = infile.is_open();
        if (infile.is_open()) {
            file2figure(infile);
        }
        infile.close();
    }


    void draw() {
        extern int nTriangles;
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        /*
        glBegin(GL_TRIANGLES);

        for (int i = 0; i < this->nr_pontos; i++) {
            glVertex3f(pontos[i][0], pontos[i][1], pontos[i][2]);
        }
        glEnd();*/

        //glColor3f(42.f/255.f,157.f/255.f,143.f/255.f);

        if (this->isTerrain){
            glBindBuffer(GL_ARRAY_BUFFER, vertices);
            glVertexPointer(3, GL_FLOAT, 0, 0);
            for (int i = 0; i < h ; i++) {
                glDrawArrays(GL_TRIANGLE_STRIP, (w) * 2 * i, (w) * 2);
            }
        } else {
            glBindBuffer(GL_ARRAY_BUFFER,this->vertices);
            glVertexPointer(3,GL_FLOAT,0,0);

            glBindBuffer(GL_ARRAY_BUFFER,this->normals);
            glNormalPointer(GL_FLOAT,0,0);

            glBindBuffer(GL_ARRAY_BUFFER, this->texCoords);
	        glTexCoordPointer(2, GL_FLOAT, 0, 0);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,this->indices);
            glDrawElements(GL_TRIANGLES,indexsCount,GL_UNSIGNED_INT,0);
            
            glBindTexture(GL_TEXTURE_2D, 0);
        }
        nTriangles+=this->indexsCount/3;
    }
};