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

Board::Board() {

}
void Board::initializeBoard(const std::string &filename) {
    // here we first open our file
    std::ifstream infile(filename);
    if (!infile) {
        std::cout << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    // we then read the file one line at a time
    while (std::getline(infile, line)) {
        if (line.empty()) continue;    // we  skip any empty lines

        // we then use a string stream to break the line into parts.
        std::istringstream iss(line);
        std::string prt;
        std::getline(iss, prt, ',');
        char bugType = prt[0];
        std::getline(iss, prt, ',');
        int id = std::stoi(prt);
        std::getline(iss, prt, ',');
        int x = std::stoi(prt);
        std::getline(iss, prt, ',');
        int y = std::stoi(prt);
        std::getline(iss, prt, ',');
        int dirInt = std::stoi(prt);
        std::getline(iss, prt, ',');
        int size = std::stoi(prt);
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

