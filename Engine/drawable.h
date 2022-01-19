//
// Created by mane on 30/03/21.
//

#ifndef ENGINE_DRAWABLE_H
#define ENGINE_DRAWABLE_H

//
// Created by mane on 29/03/21.
//

#include "gereIncludes.h"

class Drawable {
public:
    virtual void draw() = 0;
};

class Group {
private:
    list<Drawable*> desenhaveis;
    list<Group*> groups;

public:
    Group (list<Drawable*> desenhaveis, list<Group*> groups) {
        this->desenhaveis = std::move(desenhaveis);
        this->groups = groups;
    }

    void addDrawable (Drawable& draw) {
        desenhaveis.emplace_back(&draw);
    }

    void addGroup (Group& group) {
        groups.emplace_back(&group);
    }

    void setGroups (list<Group *> groups) {
        this->groups = groups;
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
