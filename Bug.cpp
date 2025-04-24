//
// Created by MyPC on 24/04/2025.
//

#include "Bug.h"
#include <cstdlib>

const int BOARD_SIZE = 10;

bool Bug::isWayBlocked()const {
    if(direction == Direction::North) return position.y == 0;
    if(direction == Direction::East) return position.x == BOARD_SIZE -1;
    if(direction == Direction::South) return position.y == BOARD_SIZE -1;
    if(direction == Direction::West) return position.x == 0;
    return true;
}

Direction Bug::getRandomDirection() const {
    int randomValue = rand()% 4 +1;
    return static_cast<Direction>(randomValue);
}