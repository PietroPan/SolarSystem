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

float radius = 30.0f;
float alpha = 0.f;
float beta = M_PI/4;
int ref[2] = {0,0};
float refAngulo[2] = {0.f,0.f};

float pos[3] = {radius*cos(beta)*sin(alpha),radius*sin(beta),radius*cos(beta)*cos(alpha)};


list<Figura3d*> figuras;

void processaMouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        switch(button) {
            case GLUT_LEFT_BUTTON:
                ref[0] = x;
                ref[1] = y;
                refAngulo[0] = alpha;
                refAngulo[1] = beta;
                break;
            case 3:  //mouse wheel scrolls
                radius -= 1;
                glutPostRedisplay();
                break;
            case 4:
                radius += 1;
                glutPostRedisplay();
                break;
            default:
                break;
        }
    }
    pos[0] = radius*cos(beta)*sin(alpha);
    pos[1] = radius*sin(beta);
    pos[2] = radius*cos(beta)*cos(alpha);

    glutPostRedisplay();
}

void mouseMovement(int x, int y) {
    float unitX = (2 * M_PI)/glutGet(GLUT_WINDOW_WIDTH);
    float unitY = M_PI/glutGet(GLUT_WINDOW_HEIGHT);

    alpha = refAngulo[0] + unitX * (ref[0]-x);

    float novoBeta = refAngulo[1] + unitY * (y-ref[1]);
    if (novoBeta <= -M_PI/2) {
        beta = -M_PI/2;
    } else if (novoBeta >= M_PI/2) {
        beta = M_PI/2;
    } else {
        beta = novoBeta;
    }


    pos[0] = radius*cos(beta)*sin(alpha);
    pos[1] = radius*sin(beta);
    pos[2] = radius*cos(beta)*cos(alpha);

    glutPostRedisplay();
}

void mousePassiveMovement(int x, int y) {
    float unitY = M_PI/glutGet(GLUT_WINDOW_HEIGHT);
    float unitX = (2 * M_PI)/glutGet(GLUT_WINDOW_WIDTH);

    alpha = unitX * (float)x;
    beta = (M_PI/2) - unitY * (float)y;

    pos[0] = radius*cos(beta)*sin(alpha);
    pos[1] = radius*sin(beta);
    pos[2] = radius*cos(beta)*cos(alpha);

    glutPostRedisplay();
}

void processaSpecialKeys(int key, int x, int y) {
    float incremento = 0.25f;

    switch (key) {
        case GLUT_KEY_UP:
            if (beta + incremento <= (M_PI/2)) {
                beta += incremento;
            }
            break;

        case GLUT_KEY_DOWN:
            if (beta - incremento >= -(M_PI/2)) {
                beta -= incremento;
            }
            break;

        case GLUT_KEY_LEFT:
            alpha-= incremento;
            break;

        case GLUT_KEY_RIGHT:
            alpha+= incremento;
            break;

        default:
            break;
    }

    pos[0] = radius*cos(beta)*sin(alpha);
    pos[1] = radius*sin(beta);
    pos[2] = radius*cos(beta)*cos(alpha);

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

    //desenhar eixos
    glBegin(GL_LINES);

    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-100.0f, 0.0f, 0.0f);
    glVertex3f(100.0f, 0.0f, 0.0f);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -100.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -100.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);

    glEnd();

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
    if (argc != 2) {
        cout << "Formato desconhecido. Usar ./Engine *path para o xml*" << endl;
    }

    list <string> filesToRead;

    TiXmlDocument doc(argv[1]);
    bool loadOk = doc.LoadFile();
    cout << loadOk;
    cout << "\n";
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
    //glutIdleFunc(renderScene);
    glutReshapeFunc(changeSize);


    glutSpecialFunc(processaSpecialKeys);
    glutMouseFunc(processaMouse);
    glutMotionFunc(mouseMovement);
    //glutPassiveMotionFunc(mousePassiveMovement);

    // some OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // enter GLUT�s main cycle
    glutMainLoop();

    return 1;
}