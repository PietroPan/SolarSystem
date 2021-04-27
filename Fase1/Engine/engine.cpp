//
// Created by mane on 10/03/21.
//

#include "gereIncludes.h"
#include "drawable.h"
#include "figura3d.cpp"
#include "transformacao.cpp"
#include "camera.h"


Camera* camera = new Camera(30.0f, 0, M_PI/4);

string pathDoXML = "";
bool axis = false;

list<Group*> grupos;

void processaMouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        switch(button) {
            case GLUT_LEFT_BUTTON:
                camera->guardaRef(x, y);
                break;
            case 3:  //mouse wheel scrolls
                camera->zoom(-1);
                break;
            case 4:
                camera->zoom(1);
                break;
            default:
                break;
        }
    }

    glutPostRedisplay();
}

void mouseMovement(int x, int y) {
    float unitX = (2 * M_PI)/glutGet(GLUT_WINDOW_WIDTH);
    float unitY = M_PI/glutGet(GLUT_WINDOW_HEIGHT);

    camera->mouseMovement(unitX, unitY, x, y);

    glutPostRedisplay();
}


void processaNormalKeys(unsigned char key, int x, int y) {
    switch(key) {
        case 99:
            camera->switchMode();
            break;
            //w 119
        case 119:
            camera->moveFPS(1);
            break;
        case 115:
            camera->moveFPS(-1);
            break;
        case 113:
            camera->incStep(1.0f);
            break;
        case 101:
            camera->decStep(1.0f);
            break;
        case 116:
            axis=!axis;
            

        default:
            break;
    }

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

    float posCamera[3], direcaoOlhar[3];
    camera->pos(posCamera);
    camera->lookAt(direcaoOlhar);
    gluLookAt(posCamera[0], posCamera[1], posCamera[2],
              direcaoOlhar[0], direcaoOlhar[1], direcaoOlhar[2],
              0.0f, 1.0f, 0.0f);

    //desenhar eixos
    if (axis==true){
        glBegin(GL_LINES);

        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-200.0f, 0.0f, 0.0f);
        glVertex3f(200.0f, 0.0f, 0.0f);

        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, -200.0f, 0.0f);
        glVertex3f(0.0f, 200.0f, 0.0f);

        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 0.0f, -200.0f);
        glVertex3f(0.0f, 0.0f, 200.0f);

        glEnd();
    }

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


    glutKeyboardFunc(processaNormalKeys);
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