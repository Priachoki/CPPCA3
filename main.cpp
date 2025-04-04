#include <iostream>
#include <string>
#include "Board.h"

using namespace std;

void displayMenu() {
    cout << "\nMenu Options:\n";
    cout << "1. Initialize Bug Board (load data from file)\n";
    cout << "2. Display all Bugs\n";
    cout << "3. Find a Bug (given an id)\n";
    cout << "4. Tap the Bug Board (move bugs only)\n";
    cout << "5. Tap the Bug Board and Fight (move bugs and resolve collisions)\n";
    cout << "6. Display Crawler's Life History\n";
    cout << "7. Display All Cells\n";
    cout << "8. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    Board board;
    bool boardInitialized = false;
    int choice;

    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore();  // Clear the newline from the input buffer

        if (choice == 1) {
            string filename;
            cout << "Enter filename (e.g., crawlerbugs.txt): ";
            getline(cin, filename);
            board.initializeBoard(filename);
            boardInitialized = true;
            cout << "Bug Board initialized from file.\n";
        } else if (choice == 2) {
            if (!boardInitialized) {
                cout << "Please initialize the Bug Board first (option 1).\n";
            } else {
                board.displayBugs();
            }
        } else if (choice == 3) {
            if (!boardInitialized) {
                cout << "Please initialize the Bug Board first (option 1).\n";
            } else {
                int id;
                cout << "Enter Bug ID to find: ";
                cin >> id;
                cin.ignore();
                board.findBug(id);
            }
        } else if (choice == 4) {
            if (!boardInitialized) {
                cout << "Please initialize the Bug Board first (option 1).\n";
            } else {
                board.tapBoard();
                cout << "Board tapped (move only). Bugs have moved.\n";
            }
        } else if (choice == 5) {
            if (!boardInitialized) {
                cout << "Please initialize the Bug Board first (option 1).\n";
            } else {
                board.tapBoardFight();
                cout << "Board tapped with fight. Bugs have moved and collisions resolved.\n";
            }
        } else if (choice == 6) {
            if (!boardInitialized) {
                cout << "Please initialize the Bug Board first (option 1).\n";
            } else {
                board.displayLifeHistory();
            }
        } else if (choice == 7) {
            if (!boardInitialized) {
                cout << "Please initialize the Bug Board first (option 1).\n";
            } else {
                board.displayCells();
            }
        } else if (choice == 8) {
            cout << "Exiting program.\n";
            return 0;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
