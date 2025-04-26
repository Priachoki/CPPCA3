
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
#include <utility>  // For pair
#include <thread>
#include <chrono>
#include "Hopper.h"
#include "SpiralBug.h"
#include <SFML/Graphics.hpp>
#include "SuperBug.h"



using namespace std;

const int BOARD_SIZE = 10;

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
        int dirInt = stoi(prt);
        getline(iss, prt, ',');
        int size = stoi(prt);
        if (bugType == 'C') {
            Position pos { x, y };
            Direction dir = static_cast<Direction>(dirInt);
            Bug* crawler = new Crawler(id, pos, dir, size);
            bugs.push_back(crawler);
        }else if(bugType == 'H'){
            getline(iss, prt, ',');
            int hopLength = stoi(prt);
            Position pos {x, y};
            Direction dir = static_cast<Direction>(dirInt);
            Bug* hopper = new Hopper(id, pos, dir, size, hopLength);
            bugs.push_back(hopper);
        }else if(bugType == 'S'){
            Position pos {x,y};
            Direction dir = static_cast<Direction>(dirInt);
            Bug* spiralBug = new SpiralBug(id, pos, dir, size);
            bugs.push_back(spiralBug);
        }
    }
    // we then close the file when done.
    infile.close();
}
//Feature 2. Display All Bugs
void Board::displayBugs() const{
    for(const auto &bug : bugs){
        if(auto hopper = dynamic_cast<Hopper*>(bug)){
            cout<< hopper ->id << "Hopper"
                <<hopper->position<< " "
                <<hopper->size<< " "
                << toString(hopper->direction) << " "
                << hopper->getHopLength() << " "
                << (hopper->alive ? "Alive" : "Dead") << endl;
        }else if(auto spiral = dynamic_cast<SpiralBug*>(bug)){
            cout <<spiral->id << "Spiral"
                 <<spiral->position << " "
                 <<spiral->size << " "
                 << toString(spiral->direction)<< " "
                 <<(spiral->alive ? "Alive" : "Dead") << endl;
        }else {
            cout << bug->id << "Crawler"
                 <<bug->position << " "
                 <<bug->size << " "
                 << toString(bug->direction)<< " "
                 <<(bug->alive ? "Alive" : "Dead") << endl;
        }
    }
}

//Feature 3. Find a bug
void Board::findBug(int id) const {
    bool found = false;
    for (const auto &bug : bugs) {
        if (bug->id == id) {
            cout << "Bug found: "
                      << bug->id << " Bug  "
                      << bug->position << " "
                      << bug->size << " "
                      << toString(bug->direction) << " "
                      << (bug->alive ? "Alive" : "Dead") << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Bug " << id << " not found." << endl;
    }
}

//Feature 4. Tap the bub board
void Board::tapBoard() {
    for (auto &bug : bugs) {
        if (bug->alive) {
            bug->move();
        }
    }
}

//feature 5. Display Life history if all bugs
void Board::displayLifeHistory() const {
    for (const auto &bug: bugs) {
        cout << bug->id << " Bug Path: ";
        for (auto it = bug->path.begin(); it != bug->path.end(); ++it) {
            cout << *it;
            if (next(it) != bug->path.end()) {
                cout << ", ";
            }
        }
        cout << endl;
    }
}

//feature 8
void Board::handleCollisions() {
    std::map<std::pair<int, int>, std::vector<Bug*>> grid;

    for (auto bug : bugs) {
        if (bug->alive) {
            int x = bug->position.x;
            int y = bug->position.y;
            if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
                grid[{x, y}].push_back(bug);
            }
        }
    }

    for (auto& cellEntry : grid) {
        std::vector<Bug*>& cellBugs = cellEntry.second;
        if (cellBugs.size() > 1) {
            int maxSize = -1;
            for (auto bug : cellBugs) {
                if (bug->size > maxSize) {
                    maxSize = bug->size;
                }
            }

            std::vector<Bug*> winners;
            for (auto bug : cellBugs) {
                if (bug->size == maxSize) {
                    winners.push_back(bug);
                }
            }

            Bug* winner = nullptr;
            if (winners.size() > 1) {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> dis(0, winners.size() - 1);
                winner = winners[dis(gen)];
            } else {
                winner = winners.front();
            }

            for (auto bug : cellBugs) {
                if (bug != winner) {
                    winner->size += bug->size;
                    bug->alive = false;
                }
            }
            cout << "Bug "<<winner->id<< " won the fight and ate:";
            for(auto bug : cellBugs){
                if(bug != winner){
                    cout << " Bug "<<bug->id;
                }
            }
            cout<<endl;
        }
    }
}
void Board::tapBoardFight() {
    for (auto &bug : bugs) {
        if (bug->alive) {
            bug->move();
        }
    }
    handleCollisions();
}

//Feature 7. Display all cells
void Board::displayCells() const {

    map<pair<int, int>, vector<Bug*>> grid;


    for (auto bug : bugs) {
        if (bug->alive) {
            grid[{bug->position.x, bug->position.y}].push_back(bug);
        }
    }


    for (int i = 0; i < BOARD_SIZE; ++i) { //i represents rows
        for (int j = 0; j < BOARD_SIZE; ++j) { //j represents columns
            cout << "(" << j << "," << i << "): ";
            pair<int, int> key = {j, i};

            if (grid.find(key) == grid.end()) {
                cout << "empty";
            } else {
                bool first = true;

                for (auto bug : grid.at(key)) {
                    if (!first) {
                        cout << ", ";
                    }
                    if(dynamic_cast<Hopper*>(bug)){
                    cout << "Hopper " << bug->id;
                    }else {
                        cout << "Crawler "<< bug->id;
                    }
                    first = false;
                }
            }
            cout << endl;
        }
    }
}
Board::~Board(){
    for(auto bug : bugs){
        delete bug;
    }
}

vector<BugInfo> Board::getBugSnapShots() const {
    vector<BugInfo> snapshot;
    for (auto bug : bugs) {
        BugInfo bugInfo;
        bugInfo.id = bug->id;
        bugInfo.position = bug->position;
        bugInfo.direction = bug->direction;
        bugInfo.size = bug->size;
        bugInfo.alive = bug->alive;

        //show type of bug
        if(auto hopper = dynamic_cast<Hopper*>(bug)){
            bugInfo.type = "Hopper";
            bugInfo.hopLength = hopper->getHopLength();
        }else if (auto spiral = dynamic_cast<SpiralBug*>(bug)) {
            bugInfo.type = "SpiralBug";
        } else{
            bugInfo.type = "Crawler";
        }

        snapshot.push_back(bugInfo);
    }
    return snapshot;
}

list<Position> Board::getBugPathById(int id) const{
    for(auto bug : bugs){
        if(bug->id == id){
            return bug->path;
        }
    }
    return {};
}

void Board::runSimulation(){
    cout <<"Starting simulation.....\n";

    while (true){
        tapBoardFight();
//        displayCells();

        //wait for a second before the next tap
        this_thread::sleep_for(chrono::seconds(1));

        int aliveCount = 0;
        Bug* lastAlive = nullptr;
        for(auto bug : bugs){
            if(bug->alive){
                aliveCount++;
                lastAlive = bug;
            }
        }
        if(aliveCount <= 1){
            if(lastAlive){
                cout<<"Bug "<<lastAlive->id<<"is the last Bug standing!!!!" <<endl;
            }else{
                cout<<"All bugs are dead. None survived!"<<endl;
            }break;
        }
    }
}

//Display the SFML
void Board::displaySFML() {
    const int boardSize = 10;
    const int cellSize = 80;
    const int cellGap = 4;

    sf::RenderWindow window(sf::VideoMode(boardSize * cellSize, boardSize * cellSize), "Bug Board");

    //Load the images
    sf::Texture crawlerTexture, hopperTexture, spiralTexture, superTexture;
    if(!crawlerTexture.loadFromFile("assets/crawler.jpeg")){
        cerr<< "Failed to load the crawler.jpeg file\n";
    }
    if(!hopperTexture.loadFromFile("assets/Hopper.jpeg")){
        cerr<< "Failed to load the Hopper.jpeg file\n";
    }
    if(!spiralTexture.loadFromFile("assets/spiral.jpeg")){
        cerr<< "Failed to load the spiral.jpeg file\n";
    }
    if (!superTexture.loadFromFile("assets/SuperBug.jpeg")) {
        cerr << "Failed to load SuperBug.jpeg file\n";
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();


            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    tapBoardFight();
                }else if (event.key.code == sf::Keyboard::Up) {
                    moveSuperBug(Direction::North);
                } else if (event.key.code == sf::Keyboard::Down) {
                    moveSuperBug(Direction::South);
                } else if (event.key.code == sf::Keyboard::Left) {
                    moveSuperBug(Direction::West);
                } else if (event.key.code == sf::Keyboard::Right) {
                    moveSuperBug(Direction::East);
                }
        }
    }


        window.clear(sf::Color::White);

        for (int i = 0; i < boardSize; ++i) {
            for (int j = 0; j < boardSize; ++j) {
                sf::RectangleShape cell(sf::Vector2f(cellSize - cellGap, cellSize - cellGap));
                cell.setPosition(j * cellSize, i * cellSize);
                cell.setFillColor(sf::Color(200, 200, 200));
                cell.setOutlineColor(sf::Color::Black);
                cell.setOutlineThickness(2);
                window.draw(cell);
            }
        }

        //Draw the bugs
        for(auto bug : bugs){
            if(!bug->alive) continue;

            sf::Sprite sprite;
            if(dynamic_cast<Hopper*>(bug)){
                sprite.setTexture(hopperTexture);
            }else if(dynamic_cast<SpiralBug*>(bug)){
                sprite.setTexture(spiralTexture);
            }else{
                sprite.setTexture(crawlerTexture);
            }

            sprite.setScale(
                    (cellSize - cellGap) / sprite.getLocalBounds().width,
                    (cellSize - cellGap) / sprite.getLocalBounds().height
            );

            sprite.setPosition(bug->position.x * cellSize, bug->position.y * cellSize);
            window.draw(sprite);
        }
        if (superBug && superBug->alive) {
            sf::Sprite sprite;
            sprite.setTexture(superTexture);
            sprite.setScale(
                    (cellSize - cellGap) / sprite.getLocalBounds().width,
                    (cellSize - cellGap) / sprite.getLocalBounds().height
            );
            sprite.setPosition(superBug->position.x * cellSize, superBug->position.y * cellSize);
            window.draw(sprite);
        }

        window.display();
    }
}

void Board::moveSelectedBug(Direction dir) {
    for (auto& bug : bugs) {
        if (bug->alive) {
            bug->direction = dir;
            bug->move();
            break;
        }
    }
}
void Board::createSuperBug() {
    Position startPos{0, 0}; // Start SuperBug at top-left
    superBug = new SuperBug(999, startPos, Direction::East, 10); // ID = 999
}

void Board::moveSuperBug(Direction dir) {
    if (superBug && superBug->alive) {
        superBug->move(dir);

        for(auto& bug : bugs){
            if (bug->alive && bug->position.x == superBug->position.x && bug->position.y == superBug->position.y) {
                if (superBug->size > bug->size) {
                    superBug->size += bug->size;
                    bug->alive = false;
                    cout << "SuperBug ate bug " << bug->id << "!\n";
                } else {
                    superBug->alive = false;
                    cout << "SuperBug was defeated by bug " << bug->id << "!\n";
                }
                break;
            }
        }
    }
}