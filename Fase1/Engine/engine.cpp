//
// Created by mane on 10/03/21.
//

#include "gereIncludes.h"
#include "drawable.h"
#include "texture.cpp"
#include "material.cpp"
#include "light.cpp"
#include "figura3d.cpp"
#include "transformacao.cpp"
#include "camera.h"

Camera* camera = new Camera(45.0f, 0, M_PI/8);

string pathDoXML = "";
bool axis = false;
bool drawCurves=false;
bool wPoints=false;
bool stop=false;
bool lines=false;

int nTriangles=0;
int timebase;
float frames;

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

    list<Group*> :: iterator it;
    for(it = grupos.begin(); it != grupos.end(); ++it) {
        Group* grp = *it;
        grp->draw();
    }

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

        glColor3f(1.0f,1.0f,1.0f);

        glEnd();
    }

    float fps;
	float time;
	frames++;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		fps = frames*(1000.0/(time-timebase));
		timebase = time;
		frames = 0;
	}

    char s[1000];
	sprintf(s,"FPS: %f - Triangles: %d",fps,nTriangles);
	glutSetWindowTitle(s);
    nTriangles=0;

    // End of frame
    glutSwapBuffers();
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
            break;
        case 108://l
            lines=!lines;
            break;
        case 109://m
            drawCurves=!drawCurves;
            break;
        case 110://n
            wPoints=!wPoints;
            break;
        case 111://o
            if (stop) {
                glutIdleFunc(NULL);
                stop=false;
            } else {
                glutIdleFunc(renderScene);
                stop=true;
            }
            break;

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

void setupScene(TiXmlElement* sceneElement){
    TiXmlElement *t = sceneElement->FirstChildElement();
    while (t != NULL){
        string instruction = t->Value();

        if (instruction == "camera"){
            TiXmlAttribute *attrib;
            for (attrib = t->FirstAttribute(); attrib != NULL; attrib = attrib->Next()) {
                string name = attrib->Name();

                if (name == "R" || name == "radius") {
                    camera->setRadius(stof(attrib->Value()));

                } else if (name == "A" || name == "alpha") {
                    camera->setAlpha(stof(attrib->Value()));

                } else if (name == "B" || name == "beta") {
                    camera->setBeta(stof(attrib->Value()));
                }
                //std::cout << attrib->Name() << " " << attrib->Value();
            }
        } else if (instruction == "iddleFunc"){
            TiXmlAttribute *attrib = t->FirstAttribute();
            if ((string)attrib->Name()=="on" && (string)attrib->Value()=="false"){
                glutIdleFunc(NULL);
            } else if  ((string)attrib->Name()=="off" && (string)attrib->Value()=="true") {
                glutIdleFunc(NULL);
            } else {
                glutIdleFunc(renderScene);
            }
        } else if (instruction == "window"){
            TiXmlAttribute *attrib;
            int width=800, height=800;
            for (attrib = t->FirstAttribute(); attrib != NULL; attrib = attrib->Next()) {
                string name = attrib->Name();

                if (name=="width"){
                    width=stoi(attrib->Value());
                } else if(name=="height"){
                    height=stoi(attrib->Value());
                }
            }
            glutReshapeWindow(width,height);
        } 
        t = t->NextSiblingElement();
    }
}

Group* setupLights (TiXmlElement* lights){
    glEnable(GL_LIGHTING);
    list<Drawable*> draws;
    list<Group*> subgroups;
    int n=0;
    TiXmlElement *light = lights->FirstChildElement();
    while (light != NULL){
        Light* l = new Light();
        TiXmlAttribute *attrib;
        string name;
        for (attrib = light->FirstAttribute(); attrib != NULL; attrib = attrib->Next()){
            name = attrib->Name();
            if (name=="type"){
                l->initLight(n,attrib->Value());
            } else if (name == "posX"){
                l->setPosX(stof(attrib->Value()));
            } else if (name == "posY"){
                l->setPosY(stof(attrib->Value()));
            } else if (name == "posZ"){
                l->setPosZ(stof(attrib->Value()));
            } else if (name == "dirX"){
                l->setDirX(stof(attrib->Value()));
            } else if (name == "dirY"){
                l->setDirY(stof(attrib->Value()));
            } else if (name == "dirZ"){
                l->setDirZ(stof(attrib->Value()));
            } else if (name == "cutOff"){
                l->setCutOff(stof(attrib->Value()));
            } else if (name == "exponent"){
                l->setExponent(stof(attrib->Value()));
            } else {
                (l->notDefault());
                    if (name == "ambR"){
                        l->hasAmb();
                        l->setAmbR(stof(attrib->Value()));
                    } else if (name == "ambG"){
                        l->hasAmb();
                        l->setAmbG(stof(attrib->Value()));
                    } else if (name == "ambB"){
                        l->hasAmb();
                        l->setAmbB(stof(attrib->Value()));
                    } else if (name == "diffR"){
                        l->hasDiff();
                        l->setDiffR(stof(attrib->Value()));
                    } else if (name == "diffG"){
                        l->hasDiff();
                        l->setDiffG(stof(attrib->Value()));
                    } else if (name == "diffB"){
                        l->hasDiff();
                        l->setDiffB(stof(attrib->Value()));
                    } else if (name == "specR"){
                        l->hasSpec();
                        l->setSpecR(stof(attrib->Value()));
                    } else if (name == "specG"){
                        l->hasSpec();
                        l->setSpecG(stof(attrib->Value()));
                    } else if (name == "specB"){
                        l->hasSpec();
                        l->setSpecB(stof(attrib->Value()));
                    } 
            }
        }
        light=light->NextSiblingElement();
        n++;
        l->setUp();
        draws.emplace_back(l);
    }

    Group *res = new Group(draws, subgroups);
    return res;
}

Group* defineGrupos (TiXmlElement* groupElement,unordered_map<string, Drawable*> &files) {
    list<Group*> subgroups;
    list<Drawable*> draws;
    string file;
    string texture;
    bool grp[6]={true,true,true,true,true,true};
    TiXmlElement *t = groupElement->FirstChildElement();

        while (t != NULL) {
            string instruction = t->Value();

            if (instruction == "translate") {
                TiXmlAttribute *attrib;
                float x = 0.0f, y = 0.0f, z = 0.0f, time = 0.0f;
                bool curve=false;
                vector<vector<float>> points;
                int i=0;

                attrib = t->FirstAttribute();
                string name = attrib->Name();
                if (name=="time" && grp[4]){
                    grp[4]=false;
                    curve=true;
                    time = stof(attrib->Value());
                    TiXmlElement *point = t->FirstChildElement("point");
                    while (point != NULL) {
                        vector<float> pointV;
                        for (attrib = point->FirstAttribute(); attrib != NULL; attrib = attrib->Next()){
                            name=attrib->Name();
                            if (name == "X" || name == "axisX") {
                                x = stof(attrib->Value());
                                //pointV.push_back(x);

                            } else if (name == "Y" || name == "axisY") {
                                y = stof(attrib->Value());
                                //pointV.push_back(z);

                            } else if (name == "Z" || name == "axisZ") {
                                z = stof(attrib->Value());
                                //pointV.push_back(y);
                            }
                        }
                        pointV.push_back(x);
                        pointV.push_back(y);
                        pointV.push_back(z);
                        points.push_back(pointV);
                        i++;
                        point = point->NextSiblingElement("point");
                    }
                    if (points.size()>=4){
                        Translacao *translation = new Translacao(x, y, z,points,curve,time);
                        draws.emplace_back(translation);
                    }
                }

                else if (grp[0]) {
                    grp[0]=false;
                    for (attrib = t->FirstAttribute(); attrib != NULL; attrib = attrib->Next()) {
                        name = attrib->Name();
                        if (name == "X" || name == "axisX") {
                            x = stof(attrib->Value());

                        } else if (name == "Y" || name == "axisY") {
                            y = stof(attrib->Value());

                        } else if (name == "Z" || name == "axisZ") {
                            z = stof(attrib->Value());
                        }
                    //std::cout << attrib->Name() << " " << attrib->Value();
                    }
                    Translacao *translation = new Translacao(x, y, z,points,curve,time);
                    draws.emplace_back(translation);
                }

            } else if (instruction == "rotate") {
                TiXmlAttribute *attrib;
                float time = 0;
                int angle = 0;
                float x = 0.0f, y = 0.0f, z = 0.0f;
                bool rotating=false;

                for (attrib = t->FirstAttribute(); attrib != NULL; attrib = attrib->Next()) {
                    string name = attrib->Name();

                    if (name == "angle" && grp[1]) {
                        grp[1]=false;
                        angle = stoi(attrib->Value());

                    } else if (name == "X" || name == "axisX") {
                        x = stof(attrib->Value());

                    } else if (name == "Y" || name == "axisY") {
                        y = stof(attrib->Value());

                    } else if (name == "Z" || name == "axisZ") {
                        z = stof(attrib->Value());
                        
                    } else if (name == "time" && grp[5]){
                        grp[5]=false;
                        rotating=true;
                        time = stof(attrib->Value());
                    }
                    //std::cout << attrib->Name() << " " << attrib->Value();
                }
                Rotacao *rotation = new Rotacao(angle,time, x, y, z,rotating);
                draws.emplace_back(rotation);

            } else if (instruction == "scale" && grp[2]) {
                grp[2]=false;
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

            } else if (instruction == "models" && grp[3]) {
                grp[3]=false;
                Material* m=new Material();
                TiXmlAttribute *attrib;
                TiXmlElement *model = t->FirstChildElement("model");
                while (model != NULL) {
                    for (attrib = model->FirstAttribute(); attrib != NULL; attrib = attrib->Next()) {
                        string name = attrib->Name();

                        if (name == "file"){

                            bool e=false;
                            file = attrib->Value();
                            if (!files.count(file)){
                                files.emplace(file,new Figura3d(pathDoXML + file));
                            }
                        } else if (name == "texture"){
                            texture = attrib->Value();
                            draws.emplace_back(new Texture(texture));

                        } else if (name == "ambR"){
                            m->setAmbR(stof(attrib->Value()));
                        } else if (name == "ambG"){
                            m->setAmbG(stof(attrib->Value()));
                        } else if (name == "ambB"){
                            m->setAmbB(stof(attrib->Value()));
                        } else if (name == "diffR"){
                            m->setDiffR(stof(attrib->Value()));
                        } else if (name == "diffG"){
                            m->setDiffG(stof(attrib->Value()));
                        } else if (name == "diffB"){
                            m->setDiffB(stof(attrib->Value()));
                        } else if (name == "specR"){
                            m->setSpecR(stof(attrib->Value()));
                        } else if (name == "specG"){
                            m->setSpecG(stof(attrib->Value()));
                        } else if (name == "specB"){
                            m->setSpecB(stof(attrib->Value()));
                        } else if (name == "emissR"){
                            m->setEmissR(stof(attrib->Value()));
                        } else if (name == "emissG"){
                            m->setEmissG(stof(attrib->Value()));
                        } else if (name == "emissB"){
                            m->setEmissB(stof(attrib->Value()));
                        } else if (name == "shine"){
                            m->setShineI(stoi(attrib->Value()));
                        }
                        
                        
                    }
                    draws.emplace_back(m);
                    draws.emplace_back(files.at(file));
                    model = model->NextSiblingElement("model");
                }

            } else if (instruction == "group") {
                subgroups.emplace_back(defineGrupos(t,files));
            } else if(instruction == "lights") {

            } else {
                cout << "INVALID SCENE\n";
                return NULL;
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
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Figura 3D");
    glewInit();
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnable(GL_TEXTURE_2D);

    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutReshapeFunc(changeSize);


    glutKeyboardFunc(processaNormalKeys);
    glutMouseFunc(processaMouse);
    glutMotionFunc(mouseMovement);
    //glutPassiveMotionFunc(mousePassiveMovement);
    // some OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    timebase = glutGet(GLUT_ELAPSED_TIME);

    

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
        TiXmlElement * s = doc.FirstChildElement( "setup" );
        if (s){
            setupScene(s);
            s = s->NextSiblingElement("scene");
        } else {
            s=doc.FirstChildElement("scene");
        }

        if(s) {
            unordered_map<string, Drawable*> files;
            TiXmlElement * l = s->FirstChildElement("lights");
            if (l){
                grupos.emplace_back(setupLights(l));
                cout << "LIGHTS\n";
            }
            TiXmlElement * g = s->FirstChildElement("group");
            while (g) {
                grupos.emplace_back(defineGrupos(g,files));
                g = g->NextSiblingElement("group");
            }
        }

    } else {
        cout << "Erro ao ler ficheiro XML->";
    }
    /*
if (string(e->Value())=="setup") {
            cout <<"oiiii\n";
            //setupScene(e);
            e = e->NextSiblingElement();
        }
        */

/*
    // Iterar sobre a lista de nomes de ficheiros, criando para cada um, um novo objeto Figura3d, que conterá os pontos a desenhar
    list<string> :: iterator it;
    for (it = filesToRead.begin(); it != filesToRead.end(); ++it) {
        string aux = *it;
        figuras.push_back(new Figura3d(aux));
    }
    */

   // enter GLUT�s main cycle
    glutMainLoop();
    

    

    return 1;
}