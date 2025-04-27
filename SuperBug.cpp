//
// Created by MyPC on 26/04/2025.
//

#include "SuperBug.h"

SuperBug::SuperBug(int id, Position position, Direction dir, int size)
        : Bug(id, position, dir, size) {}

void SuperBug::move() {
    if (!alive) return;

    direction = getRandomDirection();

    switch (direction) {
        case Direction::North:
            if (position.y > 0) position.y--;
            break;
        case Direction::East:
            if (position.x < 9) position.x++;
            break;
        case Direction::South:
            if (position.y < 9) position.y++;
            break;
        case Direction::West:
            if (position.x > 0) position.x--;
            break;
    }

    path.push_back(position);
}


void SuperBug::move(Direction dir) {
    if (!alive) return;
    direction = dir;

    switch (direction) {
        case Direction::North:
            if (position.y > 0) position.y--;
        break;
        case Direction::East:
            if (position.x < 9) position.x++;
        break;
        case Direction::South:
            if (position.y < 9) position.y++;
        break;
        case Direction::West:
            if (position.x > 0) position.x--;
        break;
    }

    path.push_back(position);
}


