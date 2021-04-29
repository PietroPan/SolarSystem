//
// Created by mane on 02/04/21.
//

#ifndef ENGINE_CAMERA_H
#define ENGINE_CAMERA_H

#include "gereIncludes.h"
#define EXPLORER true
#define FPS false

class Camera {
private:
    bool mode;

    int referencia[2];
    float refAngulo[2] = {0.f, 0.f};
    float refAngulo2[2] = {0.f, 0.f};

    float radius;
    float alpha, beta;

    // FPS camera
    float alpha2, beta2, step;

public:
    Camera(float raio, float alpha, float beta) {
        mode = EXPLORER;
        this->radius = raio;
        this->alpha = alpha;
        this->beta = beta;
        this->step = 0.5f;
    }

    void switchMode() {
        this->mode = !mode;

        if (this->mode == FPS)
        {
            float posicao[3];
            pos(posicao);

            beta2 = -beta;
            alpha2 = alpha + M_PI;
        }
    }

    void moveFPS(int dir) {
        if (mode == FPS) {
            float posicao[3], destination[3];
            pos(posicao);

            destination[0] = posicao[0] + (dir*step) * cos(beta2) * sin(alpha2);
            destination[1] = posicao[1] + (dir*step) * sin(beta2);
            destination[2] = posicao[2] + (dir*step) * cos(beta2) * cos(alpha2);

            radius = sqrt(pow(destination[0], 2)
                    + pow(destination[1], 2)
                    + pow(destination[2], 2));

            beta = asin(destination[1] / radius);
            if (beta >= M_PI / 2) {
                beta = (M_PI / 2) - 0.001f;
            } else if (beta <= -M_PI / 2) {
                beta = 0.001f - (M_PI / 2);
            }
            alpha = acos(destination[2] / (radius * cos(beta)));
            if (destination[0] < 0) {
                //alpha += 2*(M_PI - alpha);
                alpha = -alpha;
            }
        }
    }

    void zoom(float value) {
        if (mode==EXPLORER){
            radius += value;
        }
    }
    
    void incStep(float value) {
        if (mode==FPS) step += value;
    }

    void decStep(float value) {
        if ((mode==FPS)&&(step-value)>0){
            step -= value;
        }
    }

    void guardaRef(int x, int y) {
        referencia[0] = x;
        referencia[1] = y;

        refAngulo[0] = alpha;
        refAngulo[1] = beta; //será preciso isto?

        refAngulo2[0] = alpha2;
        refAngulo2[1] = beta2;
    }

    void mouseMovement(float unitX, float unitY, int x, int y) {
        if (mode == EXPLORER) {
            alpha = refAngulo[0] + unitX * (referencia[0]-x);

            float novoBeta = refAngulo[1] + unitY * (y-referencia[1]);
            if (novoBeta <= -M_PI/2) {
                beta = (-M_PI/2)+0.01;
            } else if (novoBeta >= M_PI/2) {
                beta = (M_PI/2)-0.01;
            } else {
                beta = novoBeta;
            }
        }
        else {
            alpha2 = refAngulo2[0] - unitX * (referencia[0]-x);

            float novoBeta = refAngulo2[1] + unitY * (y-referencia[1]);
            if (novoBeta <= -M_PI/2) {
                beta2 = 0.001f-M_PI/2;
            } else if (novoBeta >= M_PI/2) {
                beta2 = (M_PI/2) - 0.001f;
            } else {
                beta2 = novoBeta;
            }
        }
    }

    void pos(float arr[3]) {
        arr[0] = radius * cos(beta) * sin(alpha);
        arr[1] = radius * sin(beta);
        arr[2] = radius * cos(beta) * cos(alpha);
    }

    void lookAt(float arr[3]) {
        if (mode == EXPLORER) {
            arr[0] = arr[1] = arr[2] = 0.0f;
        } else {
            float posicao[3];
            pos(posicao);
            arr[0] = posicao[0] + cos(beta2) * sin(alpha2);
            arr[1] = posicao[1] + sin(beta2);
            arr[2] = posicao[2] + cos(beta2) * cos(alpha2);

        }
    }
};
#endif //ENGINE_CAMERA_H
