//
// Created by mane on 29/03/21.
//
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifndef ENGINE_DRAWABLE_H
#define ENGINE_DRAWABLE_H

#include <list>
#include <iostream>

using namespace std;


class Drawable {
public:
    virtual void draw() = 0;
};

class Group {
private:
    list<Drawable*> desenhaveis;
    list<Group*> groups;

public:
    Group() {
    }

    void draw() {
        glPushMatrix();
        list <Drawable*> :: iterator it;
        for(it = desenhaveis.begin(); it != desenhaveis.end(); ++it) {
            Drawable* d = *it;
            d->draw();
        }

        list <Group*> :: iterator it2;
        for(it2 = groups.begin(); it2 != groups.end(); ++it2) {
            Group* g = *it2;
            g->draw();
        }
        glPopMatrix();
    }
};


#endif //ENGINE_DRAWABLE_H
