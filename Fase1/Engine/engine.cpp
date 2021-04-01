//
// Created by mane on 10/03/21.
//

#include "gereIncludes.h"
#include "drawable.h"
#include "figura3d.cpp"
#include "transformacao.cpp"

float radius = 30.0f;
float alpha = 0.f;
float beta = M_PI/4;
int ref[2] = {0,0};
float refAngulo[2] = {0.f,0.f};

float pos[3] = {radius*cos(beta)*sin(alpha),radius*sin(beta),radius*cos(beta)*cos(alpha)};

string pathDoXML = "";

list<Group*> grupos;

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

    list<Group*> :: iterator it;
    for(it = grupos.begin(); it != grupos.end(); ++it) {
        Group* grp = *it;
        grp->draw();
    }

    // End of frame
    glutSwapBuffers();
}

Group* defineGrupos (TiXmlElement* groupElement) {
    list<Group*> subgroups;
    list<Drawable*> draws;

    TiXmlElement *t = groupElement->FirstChildElement();

        while (t != NULL) {
            string instruction = t->Value();

            if (instruction == "translate") {
                TiXmlAttribute *attrib;
                float x = 0.0f, y = 0.0f, z = 0.0f;

                for (attrib = t->FirstAttribute(); attrib != NULL; attrib = attrib->Next()) {
                    string name = attrib->Name();
                    if (name == "X" || name == "axisX") {
                        x = stof(attrib->Value());

                    } else if (name == "Y" || name == "axisY") {
                        y = stof(attrib->Value());

                    } else if (name == "Z" || name == "axisZ") {
                        z = stof(attrib->Value());
                    }
                    //std::cout << attrib->Name() << " " << attrib->Value();
                }
                Translacao *translation = new Translacao(x, y, z);
                draws.emplace_back(translation);


            } else if (instruction == "rotate") {
                TiXmlAttribute *attrib;
                int angle = 0;
                float x = 0.0f, y = 0.0f, z = 0.0f;

                for (attrib = t->FirstAttribute(); attrib != NULL; attrib = attrib->Next()) {
                    string name = attrib->Name();

                    if (name == "angle") {
                        angle = stoi(attrib->Value());

                    } else if (name == "X" || name == "axisX") {
                        x = stof(attrib->Value());

                    } else if (name == "Y" || name == "axisY") {
                        y = stof(attrib->Value());

                    } else if (name == "Z" || name == "axisZ") {
                        z = stof(attrib->Value());
                    }
                    //std::cout << attrib->Name() << " " << attrib->Value();
                }

                Rotacao *rotation = new Rotacao(angle, x, y, z);
                draws.emplace_back(rotation);

            } else if (instruction == "scale") {
                TiXmlAttribute *attrib;
                float x = 0.0f, y = 0.0f, z = 0.0f;

                for (attrib = t->FirstAttribute(); attrib != NULL; attrib = attrib->Next()) {
                    string name = attrib->Name();

                    if (name == "X" || name == "axisX") {
                        x = stof(attrib->Value());

                    } else if (name == "Y" || name == "axisY") {
                        y = stof(attrib->Value());

                    } else if (name == "Z" || name == "axisZ") {
                        z = stof(attrib->Value());
                    }
                    //std::cout << attrib->Name() << " " << attrib->Value();
                }
                Escala *scale = new Escala(x, y, z);
                draws.emplace_back(scale);

            } else if (instruction == "models") {
                TiXmlElement *model = t->FirstChildElement("model");
                while (model != NULL) {
                    string file = model->Attribute("file");
                    draws.emplace_back(new Figura3d(pathDoXML + file));
                    model = model->NextSiblingElement("model");
                }

            } else if (instruction == "group") {
                subgroups.emplace_back(defineGrupos(t));
            }

            t = t->NextSiblingElement();

        }
    Group *res = new Group(draws, subgroups);
    return res;
}

void guardaPath3d(char* copiaPath) {
    int index = 0;
    for (int i = 0; copiaPath[i]; i++) {
        if (copiaPath[i] == '/') {
            index = i;
        }
    }
    if (index != 0) {
        copiaPath[index] = '\0';
    }
}


int main(int argc, char** argv)
{
    if (argc != 2) {
        cout << "Formato desconhecido. Usar ./Engine *path para o xml*" << endl;
    }

    char *copiaPath = new char[255];
    strcpy(copiaPath, argv[1]);
    guardaPath3d(copiaPath);
    pathDoXML = string(copiaPath) + "/";
    //cout << "O path para o xml é " << pathDoXML << endl;

    list <string> filesToRead;

    TiXmlDocument doc(argv[1]);
    bool loadOk = doc.LoadFile();
    cout << loadOk;
    cout << "\n";
    if (loadOk) {
        TiXmlElement * scene = doc.FirstChildElement( "scene" );

        if(scene) {
            TiXmlElement * g = scene->FirstChildElement("group");
            while (g) {
                grupos.emplace_back(defineGrupos(g));
                g = g->NextSiblingElement("group");
            }
        }

    } else {
        cout << "Erro ao ler ficheiro XML.";
    }


/*
    // Iterar sobre a lista de nomes de ficheiros, criando para cada um, um novo objeto Figura3d, que conterá os pontos a desenhar
    list<string> :: iterator it;
    for (it = filesToRead.begin(); it != filesToRead.end(); ++it) {
        string aux = *it;
        figuras.push_back(new Figura3d(aux));
    }
    */

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