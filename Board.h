//
// Created by MyPC on 31/03/2025.
//

#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <string>
#include "Crawler.h"


class Board {
public:
    Board();

    void initializeBoard(const std::string &filename);
    void displayBugs() const;
    void findBug(int id) const;
    void tapBoard();
    void displayLifeHistory() const;
    void displayCells() const;
    void tapBoardFight();
    void runSimulation();


private:
    std::vector<Crawler*> crawlers;
};



#endif //BOARD_H
