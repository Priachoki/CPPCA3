//
// Created by MyPC on 26/04/2025.
//

#ifndef SUPERBUG_H
#define SUPERBUG_H



#include "Bug.h"

class SuperBug : public Bug {
public:
    SuperBug(int id, Position pos, Direction dir, int size);
    void move();
    void move(Direction dir);
};



#endif //SUPERBUG_H
