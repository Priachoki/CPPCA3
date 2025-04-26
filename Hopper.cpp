#include "Hopper.h"
#include <cstdlib> // For rand()

Hopper::Hopper(int id, Position pos, Direction dir, int size, int hopLength)
        : Bug(id, pos, dir, size), hopLength(hopLength) {}

void Hopper::move() {
    if (!alive) return;

    while (isWayBlocked()) {
        direction = getRandomDirection();
    }

    int actualHop = hopLength;

    switch (direction) {
        case Direction::North:
            if (position.y - hopLength < 0) {
                actualHop = position.y;
            }
            position.y -= actualHop;
            break;

        case Direction::South:
            if (position.y + hopLength >= 10) {
                actualHop = 9 - position.y;
            }
            position.y += actualHop;
            break;

        case Direction::East:
            if (position.x + hopLength >= 10) {
                actualHop = 9 - position.x;
            }
            position.x += actualHop;
            break;

        case Direction::West:
            if (position.x - hopLength < 0) {
                actualHop = position.x;
            }
            position.x -= actualHop;
            break;
    }

    path.push_back(position);
}
