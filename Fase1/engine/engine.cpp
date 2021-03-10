//
// Created by mane on 10/03/21.
//

#include <cstring>
#include "figura3d.cpp"

float pontosPlano[][3] = {{1.0f, 0.0f, 1.0f},
                          {1.0f, 0.0f, -1.0f},
                          {-1.0f, 0.0f, 1.0f},
                          {-1.0f, 0.0f, 1.0f},
                          {1.0f, 0.0f, -1.0f},
                          {-1.0f, 0.0f, -1.0f}};

Plano* p = new Plano(6, pontosPlano);

list<Figura3d*> figuras;

Figura3d* file2Figure(string nomeFicheiro) {
    ifstream infile(nomeFicheiro.c_str());
    //infile.open(nomeFicheiro);
    bool teste = infile.is_open();
    if (teste) {
        cout << "Abriu o ficheiro" << endl;
        char tipoFigura[50];
        infile.getline(tipoFigura, 50);
        cout << "O tipo da figura é " << (string) tipoFigura << endl;

        if (strcmp(tipoFigura, "plane") == 0) return new Plano(infile);
    }

    infile.close();
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


void renderScene(void)
{
    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set camera
    glLoadIdentity();
    gluLookAt(5.0,5.0,5.0,
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



void printInfo() {

    printf("Vendor: %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version: %s\n", glGetString(GL_VERSION));
}


int main(int argc, char** argv)
{
    figuras.push_back(file2Figure("/home/mane/github/CG/Fase1/engine/plane.txt"));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Figura3D");

    glutDisplayFunc(renderScene);
    //glutIdleFunc(renderScene);
    glutReshapeFunc(changeSize);

    // some OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // enter GLUT�s main cycle
    glutMainLoop();

    return 1;
}