//
// Created by priya on 3/29/2025.
//

#ifndef CPPCA3_DIRECTION_H
#define CPPCA3_DIRECTION_H

#include <string>
enum class Direction {
    North = 1,
    East,
    South,
    West
};
//Helper function to convert a Direction enum to a readable string.
inline std::string toString(Direction dir){
    switch(dir){
        case Direction::North: return "North";
        case Direction::East: return "East";
        case Direction::South: return"South";
        case Direction::West: return"West";
        default:              return"Unknown";
    }
}

#endif //CPPCA3_DIRECTION_H
