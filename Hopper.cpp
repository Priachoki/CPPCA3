//
// Created by priya on 4/24/2025.
//

#include "Hopper.h"
Hopper::Hopper(int id, Position pos, Direction dir, int size, int hopLength)
        : Bug(id, pos, dir, size), hopLength(hopLength){}

void Hopper::move(){

    while(isWayBlocked()){
        direction = getRandomDirection();
    }

    int actualHop = hopLength;

    if(direction == Direction::North){
        if(position.y - hopLength < 0){
            actualHop= position.y;
        }
        position.y -= actualHop;
    }else if (direction == Direction::South){
        if(position.y +hopLength >= 10){
            actualHop = 9 - position.y;
        }
        position.y += actualHop;
    }else if(direction == Direction::West){
        if(position.x - hopLength < 0){
            actualHop = position.x;
        }
        position.x -= actualHop;
    }
    path.push_back(position);
}