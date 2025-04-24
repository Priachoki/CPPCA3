//
// Created by MyPC on 31/03/2025.
//

#include "Crawler.h"

Crawler::Crawler(int id, Position pos, Direction dir, int size)
        : Bug(id, pos,dir,size){}

void Crawler::move(){
    while(isWayBlocked()){
        direction = getRandomDirection();
    }

    if(direction == Direction::North){
        position.y -= 1;
    }else if (direction == Direction::East){
        position.x += 1;
    }else if(direction == Direction::South){
        position.y +=1;
    }else if(direction == Direction::West){
        position.x -= 1;
    }

    path.push_back(position);
}

