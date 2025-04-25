//
// Created by priya on 4/24/2025.
//

#ifndef CPPCA3_BUGINFO_H
#define CPPCA3_BUGINFO_H

#include "Direction.h"
#include "Bug.h"

struct BugInfo{
    int id;
    Position position;
    Direction direction;
    int size;
    bool alive;
    string type;
    int hopLength = 0;
};

#endif //CPPCA3_BUGINFO_H
