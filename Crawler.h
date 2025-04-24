//
// Created by MyPC on 31/03/2025.
//

#include <list>
#include "Direction.h"
#include <iostream>
#ifndef CRAWLER_H
#define CRAWLER_H

#include "Bug.h"
using namespace std;

class Crawler : public Bug{
public:
    Crawler(int id, Position pos, Direction dir, int size);
    void move() override;
};

#endif //CRAWLER_H
