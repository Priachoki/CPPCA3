//
// Created by Innoe on 24/04/2025.
//

#ifndef CPPCA3_BUG_H
#define CPPCA3_BUG_H

#include <list>
#include "Direction.h"
#include <ostream>
using namespace std;

struct Position{
    int x;
    int y;

    friend ostream& operator<<(ostream& os, const Position& pos){
        os << "(" <<pos.x << "," << pos.y << ")";
        return os;
    }
    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};
class Bug {
public:
    Bug(int id, Position pos, Direction dir, int size)
      : id(id), position(pos), direction(dir), size(size), alive(true){
        path.push_back(position);
    }

    virtual ~Bug() = default;

    int id;
    Position position;
    Direction direction;
    int size;
    bool alive;
    list<Position> path;

    virtual void move() = 0;
    bool isWayBlocked() const;

protected:
    Direction getRandomDirection() const;
};


#endif //CPPCA3_BUG_H