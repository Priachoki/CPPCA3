#include "SpiralBug.h"

SpiralBug::SpiralBug(int id, Position position, Direction dir, int size)
    : Bug(id, position, dir, size), stepsTaken(0), stepsInCurrentDirection(0),maxSteps(1), directionIndex(0){}

    void SpiralBug::move(){
    if(!alive) return;
        int newX = position.x;
        int newY = position.y;

    switch(directionIndex % 4){
        case 0: newX++; break; // EAst
        case 1: newY++; break; //South
        case 2: newX--; break; //West
        case 3: newY--; break; //North
    }

    //check if the spirial has reach board bounds
    if(newX >= 0 && newX < 10 && newY >= 0 && newY < 10){
        position.x = newX;
        position.y = newY;
        path.push_back(position);
    }

    stepsTaken++;
    stepsInCurrentDirection++;

    if(stepsInCurrentDirection == maxSteps){
        directionIndex = (directionIndex =1) % 4;
        stepsInCurrentDirection = 0;

        if(directionIndex % 2 == 0){
            maxSteps++; //Increments steps after every 2 turns
        }
    }
    path.push_back(position);
}