//
// Created by priya on 4/24/2025.
//

#ifndef CPPCA3_HOPPER_H
#define CPPCA3_HOPPER_H

#include "Bug.h"


class Hopper : public Bug {
public:
    Hopper(int id, Position pos, Direction dir, int size, int hopLength);
    void move() override;

    int getHopLength() const {
        return hopLength;
    }

private:
    int hopLength;
};


#endif //CPPCA3_HOPPER_H
