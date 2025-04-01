//
// Created by MyPC on 31/03/2025.
//

#include <list>
#include "Direction.h"
#include <iostream>
#ifndef CRAWLER_H
#define CRAWLER_H

using namespace std;

struct Position {
    int x;
    int y;
};


class Crawler {
public:

    Crawler(int id, Position pos, Direction dir, int size);


    int id;
    Position position;
    Direction direction;
    int size;
    bool alive;
    std::list<Position> path;

    void move();
    bool isWayBlocked() const;
private:

    Direction getRandomDirection() const;
};

#endif //CRAWLER_H
