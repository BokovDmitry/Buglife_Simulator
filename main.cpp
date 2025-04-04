#include <iostream>

#include "src/Board.h"

using namespace std;

void displayBugs(const Board& board) {
    board.displayBugs();
}

void displayBugsHistory(const Board& board) {
    board.displayLifeHistory();
}

void displayCells(const Board& board) {
    board.displayCells();
}

void runSimulation(Board& board) {
    board.runSimulation();
}

void getCrawler (const Board& board) {
    string id;
    cout << "Please, enter crawler id: ";
    cin >> id;

    try {
        const Crawler* crawler = board.getCrawler(stoi(id));
        if (crawler) {
            crawler->display();
        } else {
            cout << "Crawler with ID " << id << " was not found. Please check and try again!" << endl;
        }
    } catch (const exception& e) {
        cout << "Invalid input. Please try again." << endl;
    }
}

void menu() {
    int choice;
    Board board;
    // board.initializeBoard("data/crawler-bugs.txt");
    do {
        cout << "\n----------MENU----------" << endl;
        cout << "1. Initialize Bug Board" << endl;
        cout << "2. Display all bugs" << endl;
        cout << "3. Display bug by ID" << endl;
        cout << "4. TAP!" << endl;
        cout << "5. Display Bugs' History" << endl;
        cout << "6. Display Cells" << endl;
        cout << "7. Run Simulation" << endl;
        cout << "0. Exit" << endl;

        try {
            cout << "\nEnter option: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    board.initializeBoard("data/crawler-bugs.txt");
                    cout << "Bug board initialized successfully!" << endl;
                    break;
                case 2:
                    displayBugs(board);
                    break;
                case 3:
                    getCrawler(board);
                    break;
                case 4:
                    board.tap();
                    displayBugs(board);
                    break;
                case 5:
                    displayBugsHistory(board);
                    break;
                case 6:
                    displayCells(board);
                    break;
                case 7:
                    runSimulation(board);
                    break;
                case 0:
                    cout << "Exiting..." << endl;
                    break;
                default:
                    cout << "Invalid option. Please try again." << endl;
                    break;
            }
        } catch (const std::exception& e) {
            cout << "No Such Option" << endl;
        }
    } while (choice != 0);
}

int main() {
    srand(time(0));
    menu();
}
