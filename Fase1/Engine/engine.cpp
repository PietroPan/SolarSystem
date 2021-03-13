//
// Created by mane on 10/03/21.
//

#include <cstring>
#include <string>
#include "figura3d.cpp"
#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"

#define _USE_MATH_DEFINES
#include <math.h>

#define DIST 30

float alpha = 0.f;
float beta = M_PI/4;

float pos[3] = {(float)DIST*cos(beta)*sin(alpha),((float) DIST)*sin(beta),(float)DIST*cos(beta)*cos(alpha)};


list<Figura3d*> figuras;

void processaSpecialKeys(int key, int x, int y) {
    float incremento = 0.25f;

    switch (key) {
        //w
        case GLUT_KEY_UP:
            if (beta + incremento <= (M_PI/2)) {
                beta += incremento;
            }
            break;

        //s
        case GLUT_KEY_DOWN:
            if (beta - incremento >= -(M_PI/2)) {
                beta -= incremento;
            }
            break;

        //a
        case GLUT_KEY_LEFT:
            alpha-= incremento;
            break;

        //d
        case GLUT_KEY_RIGHT:
            alpha+= incremento;
            break;
        default:
            break;

    }
    pos[0] = (float)DIST*cos(beta)*sin(alpha);
    pos[1] = (float)DIST*sin(beta);
    pos[2] = (float)DIST*cos(beta)*cos(alpha);

    glutPostRedisplay();

}


void changeSize(int w, int h)
{
    // Prevent a divide by zero, when window is too short
    // (you can�t make a window with zero width).
    if (h == 0)
        h = 1;
    // compute window's aspect ratio
    float ratio = w * 1.0f / h;
    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load the identity matrix
    glLoadIdentity();
    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);
    // Set the perspective
    gluPerspective(45.0f, ratio, 1.0f, 1000.0f);
    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}


void renderScene(void) {
    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set camera
    glLoadIdentity();
    gluLookAt(pos[0], pos[1], pos[2],
              0.0,0.0,0.0,
              0.0f,1.0f,0.0f);

    list<Figura3d*> :: iterator it;
    for (it = figuras.begin(); it != figuras.end(); ++it) {
        Figura3d* aux = *it;
        aux->draw();
    }

    // End of frame
    glutSwapBuffers();
}


int main(int argc, char** argv)
{
    list <string> filesToRead;

    TiXmlDocument doc( "scene.xml" );
    bool loadOk = doc.LoadFile();

    if (loadOk) {
        TiXmlElement * scene = doc.FirstChildElement( "scene" );
        if( scene ) {
            TiXmlElement * figure = scene->FirstChildElement( "model" );
            if (figure) {
                filesToRead.emplace_back(figure->Attribute("file"));

                TiXmlElement * figures = figure->NextSiblingElement("model");

                while (figures!=NULL) {
                    filesToRead.emplace_back(figures->Attribute("file"));
                    figures = figures->NextSiblingElement("model");
                }

            }
        }

    } else {
        cout << "Erro ao ler ficheiro XML.";
    }



    // Iterar sobre a lista de nomes de ficheiros, criando para cada um, um novo objeto Figura3d, que conterá os pontos a desenhar
    list<string> :: iterator it;
    for (it = filesToRead.begin(); it != filesToRead.end(); ++it) {
        string aux = *it;
        figuras.push_back(new Figura3d(aux));
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Figura 3D");

    glutDisplayFunc(renderScene);
    //glutIdleFunc(renderScene); Descomentar para ativar rave mode :)
    glutReshapeFunc(changeSize);

    glutSpecialFunc(processaSpecialKeys);

    // some OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // enter GLUT�s main cycle
    glutMainLoop();

    return 1;
}