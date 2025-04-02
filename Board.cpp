//
// Created by MyPC on 31/03/2025.
//

#include "Board.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>
const int BOARD_SIZE = 10;

using  namespace std;

Board::Board() {

}
void Board::initializeBoard(const string &filename) {
    // here we first open our file
     ifstream infile(filename);
    if (!infile) {
        cout << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    // we then read the file one line at a time
    while (getline(infile, line)) {
        if (line.empty()) continue;    // we  skip any empty lines

        // we then use a string stream to break the line into parts.
        istringstream iss(line);
        string prt;
        getline(iss, prt, ',');
        char bugType = prt[0];
        getline(iss, prt, ',');
        int id = stoi(prt);
        getline(iss, prt, ',');
        int x = stoi(prt);
        getline(iss, prt, ',');
        int y = stoi(prt);
        getline(iss, prt, ',');
        int dirInt =stoi(prt);
        getline(iss, prt, ',');
        int size = stoi(prt);
        if (bugType == 'C') {
            Position pos { x, y };
            Direction dir = static_cast<Direction>(dirInt);
            Crawler* crawler = new Crawler(id, pos, dir, size);
            crawlers.push_back(crawler);
        }
    }
    // we then close the file when done.
    infile.close();
}

void Board::displayBugs() const {
    for (const auto &crawler : crawlers) {
        cout << crawler->id << " Crawler "
                  << crawler->position << " "
                  << crawler->size << " "
                  << toString(crawler->direction) << " "
                  << (crawler->alive ? "Alive" : "Dead") << endl;
    }
}
void Board::findBug(int id) const {
    bool found = false;
    for (const auto &crawler : crawlers) {
        if (crawler->id == id) {
            cout << "Bug found: "
                      << crawler->id << " Crawler "
                      << crawler->position << " "
                      << crawler->size << " "
                      << toString(crawler->direction) << " "
                      << (crawler->alive ? "Alive" : "Dead") << endl;
            found = true;
            break;
        }
    }
    if (!found) {
      cout << "Bug " << id << " not found." << endl;
    }
}
void Board::tapBoard() {
    for (auto &crawler : crawlers) {
        if (crawler->alive) {
            crawler->move();
        }
    }
}
// Feature 5: Display Life History of all bugs
 void Board::displayLifeHistory() const {
    for (const auto &crawler : crawlers) {
        cout << crawler->id << " Crawler Path: ";
        for (auto it = crawler->path.begin(); it != crawler->path.end(); ++it) {
           cout << *it;
            if (next(it) != crawler->path.end()) {
                cout << ", ";
            }
        }
        cout << endl;
    }
}