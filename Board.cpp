//
// Created by MyPC on 31/03/2025.
//

#include "Board.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>
#include <map>
#include <utility>
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

void Board::displayBugs() const {
    for (const auto &crawler : crawlers) {
        std::cout << crawler->id << " Crawler "
                  << crawler->position << " "
                  << crawler->size << " "
                  << toString(crawler->direction) << " "
                  << (crawler->alive ? "Alive" : "Dead") << std::endl;
    }
}
void Board::findBug(int id) const {
    bool found = false;
    for (const auto &crawler : crawlers) {
        if (crawler->id == id) {
            std::cout << "Bug found: "
                      << crawler->id << " Crawler "
                      << crawler->position << " "
                      << crawler->size << " "
                      << toString(crawler->direction) << " "
                      << (crawler->alive ? "Alive" : "Dead") << std::endl;
            found = true;
            break;
        }
    }
    if (!found) {
        std::cout << "Bug " << id << " not found." << std::endl;
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
void Board::handleCollisions() {
    // Create a map that uses a pair (x, y) as a key and a vector of Crawler* as its value.
    std::map<std::pair<int, int>, std::vector<Crawler*>> grid;

    // Place each alive crawler into the appropriate cell in the map.
    for (auto crawler : crawlers) {
        if (crawler->alive) {
            int x = crawler->position.x;
            int y = crawler->position.y;
            if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
                // The key is a pair (x, y) indicating the cell coordinates.
                grid[{x, y}].push_back(crawler);
            }
        }
    }

    // Iterate over each cell in the map.
    for (auto& cellEntry : grid) {
        std::vector<Crawler*>& cellCrawlers = cellEntry.second;
        if (cellCrawlers.size() > 1) {
            // Determine the maximum size among bugs in this cell.
            int maxSize = -1;
            for (auto crawler : cellCrawlers) {
                if (crawler->size > maxSize) {
                    maxSize = crawler->size;
                }
            }
            // Collect all bugs with the maximum size.
            std::vector<Crawler*> winners;
            for (auto crawler : cellCrawlers) {
                if (crawler->size == maxSize) {
                    winners.push_back(crawler);
                }
            }
            // Choose one winner randomly if there's a tie.
            Crawler* winner = nullptr;
            if (winners.size() > 1) {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> dis(0, winners.size() - 1);
                winner = winners[dis(gen)];
            } else {
                winner = winners.front();
            }
            // The winner eats all other bugs: grows in size and marks losers as dead.
            for (auto crawler : cellCrawlers) {
                if (crawler != winner) {
                    winner->size += crawler->size;
                    crawler->alive = false;
                }
            }
        }
    }
}
void Board::tapBoardFight() {
    // Move each alive bug
    for (auto &crawler : crawlers) {
        if (crawler->alive) {
            crawler->move();
        }
    }
    // Resolve collisions (fight/eat)
    handleCollisions();
}
#include <map>
#include <utility>  // For std::pair

void Board::displayCells() const {
    // Create a map where the key is a pair (x, y) representing cell coordinates,
    // and the value is a vector of pointers to Crawler objects in that cell.
    std::map<std::pair<int, int>, std::vector<Crawler*>> grid;

    // Place each alive crawler into the appropriate cell in the map.
    for (auto crawler : crawlers) {
        if (crawler->alive) {
            int x = crawler->position.x;
            int y = crawler->position.y;
            if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
                grid[{x, y}].push_back(crawler);
            }
        }
    }

    // Iterate over every cell in our fixed board (0,0) to (BOARD_SIZE-1, BOARD_SIZE-1).
    for (int i = 0; i < BOARD_SIZE; ++i) {         // i represents the y-coordinate (row)
        for (int j = 0; j < BOARD_SIZE; ++j) {     // j represents the x-coordinate (column)
            std::cout << "(" << j << "," << i << "): ";
            std::pair<int, int> key = {j, i};
            // Check if there is an entry in the map for this cell.
            if (grid.find(key) == grid.end() || grid.at(key).empty()) {
                std::cout << "empty";
            } else {
                bool first = true;
                // Print each bug in the cell.
                for (auto crawler : grid.at(key)) {
                    if (!first) {
                        std::cout << ", ";
                    }
                    std::cout << "Crawler " << crawler->id;
                    first = false;
                }
            }
            std::cout << std::endl;
        }
    }
}
