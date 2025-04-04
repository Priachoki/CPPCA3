#include <iostream>
#include <string>
#include "Board.h"

using namespace std;

void displayMenu() {
    cout << "\nMenu Options:\n";
    cout << "1. Initialize Bug Board (load data from file)\n";
    cout << "2. Display all Bugs\n";
    cout << "3. Find a Bug (given an id)\n";
    cout << "4. Tap the Bug Board (move bugs)\n";
    cout << "5. Display Crawler's life History\n";
    cout<<  "6. Display Cells\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    Board board;
    bool boardInitialized = false;
    int choice;

    while(true) {
        displayMenu();
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1: {
                string filename;
                cout << "Enter filename (e.g., crawlerbugs.txt): ";
                getline(cin, filename);
                board.initializeBoard(filename);
                boardInitialized = true;
                cout << "Bug Board initialized from file.\n";
                break;
            }
            case 2: { if (!boardInitialized) {
                    cout << "Please initialize the Bug Board first (option 1).\n";
                } else {
                    board.displayBugs();
                }
                break;
            }
            case 3: {
                if (!boardInitialized) {
                    cout << "Please initialize the Bug Board first (option 1).\n";
                } else {
                    int id;
                    cout << "Enter Bug ID to find: ";
                    cin >> id;
                    cin.ignore();
                    board.findBug(id);
                }
                break;
            }
            case 4: {
                if (!boardInitialized) {
                    cout << "Please initialize the Bug Board first (option 1).\n";
                } else {
                    board.tapBoard();
                    cout << "Board tapped. Bugs have moved.\n";
                }
                break;
            }
            case 5: {
                if (!boardInitialized) {
                    cout << "Please initialize the board first (option 1).\n";
                }
                board.displayLifeHistory();
                break;
            }
            case 6: {
                if (!boardInitialized) {
                    cout << "Please initialize the board first (option 1).\n";
                }
                board.tapBoardFight();
            }

            case 7: {
                cout << "Exiting program.\n";
                return 0;
            }
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.