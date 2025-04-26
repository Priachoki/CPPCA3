#ifndef SPIRALBUG_H
#define SPIRALBUG_H

#include "Bug.h"

class SpiralBug  : public Bug{
private:
    int stepsTaken;
    int stepsInCurrentDirection;
    int maxSteps;
    int directionIndex; //0 for East, 1 for South, 2 for West and 3 for North

public:
    SpiralBug(int id, Position position, Direction dir, int size);
    void move() override;
};

#endif //CPPCA3_SPIRALBUG_H