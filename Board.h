

 //
// Created by MyPC on 31/03/2025.
//

#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <string>
#include "Crawler.h"
#include "Bug.h"
#include "Hopper.h"
#include "BugInfo.h"
#include "SuperBug.h"


using namespace std;

class Board {
public:
    Board();
    ~Board();

    void initializeBoard(const string &filename);
    void displayBugs() const;
    void findBug(int id) const;
    void tapBoard();

    void displayLifeHistory() const;
    void displayCells() const;
    void tapBoardFight();
    void runSimulation();
    void displaySFML();
    void moveSelectedBug(Direction dir);
    void moveSuperBug(Direction dir);
    void createSuperBug();


    SuperBug* getSuperBug() const {
        return superBug;
    }
    vector<BugInfo> getBugSnapShots() const;
    list<Position> getBugPathById(int id) const;




private:
    vector<Bug*> bugs;
    void handleCollisions();
    SuperBug* superBug = nullptr;
};



#endif //BOARD_H