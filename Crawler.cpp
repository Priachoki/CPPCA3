//
// Created by MyPC on 31/03/2025.
//

#include "Crawler.h"
#include <iostream>
#include <random>
#include <chrono>
#include <cstdlib>

const int BOARD_SIZE = 10;

Crawler::Crawler(int id, Position pos, Direction dir, int size):

id(id), position(pos),direction(dir),size(size),alive(true)
{
    //to record the starting position of our bug in our path history
    path.push_back(position);
}

bool Crawler::isWayBlocked() const {
    if (direction == Direction::North) {
        return (position.y == 0);
    } else if (direction == Direction::East) {
        return (position.x == BOARD_SIZE - 1);
    } else if (direction == Direction::South) {
        return (position.y == BOARD_SIZE - 1);
    } else if (direction == Direction::West) {
        return (position.x == 0);
    } else {

        return true;
    }
}


Direction Crawler::getRandomDirection() const {
    // Generate a random number between 1 and 4.
    int randomValue = rand() % 4 + 1;
    return static_cast<Direction>(randomValue);
}
void Crawler::move() {
    // We check to see if the bug is blocked ( that is at the edge of the board).
    // If it is we  choose a new random direction until it can move.
    while (isWayBlocked()) {
        // getRandomDirection() gives us a new random direction (North, East, South, or West)
        direction = getRandomDirection();
    }

    // Then we move the bug one unit in the direction it is now facing.

    if (direction == Direction::North) {
        // moving North means going up on the board,so we decrease the y-coordinate by 1
        position.y = position.y - 1;
    }
    else if (direction == Direction::East) {
        // moving East means going right, so we increase the x-coordinate by 1
        position.x = position.x + 1;
    }
    else if (direction == Direction::South) {
        // Moving South means going down,so we increase the y-coordinate by 1.
        position.y = position.y + 1;
    }
    else if (direction == Direction::West) {
        // Moving West means going left,so we decrease the x-coordinate by 1.
        position.x = position.x - 1;
    }

    // and then we take note of  the new position in the bug's path history.This lets us remember where the bug has been.
    path.push_back(position);
}
