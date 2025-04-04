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
    board.initializeBoard("data/crawler-bugs.txt");
    do {
        cout << "\n----------MENU----------" << endl;
        cout << "1. Display all bugs" << endl;
        cout << "2. Display bug by ID" << endl;
        cout << "3. TAP!" << endl;
        cout << "4. Display Bugs' History" << endl;
        cout << "5. Display Cells" << endl;
        cout << "6. Run Simulation" << endl;
        cout << "0. Exit" << endl;

        try {
            cout << "\nEnter option: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    displayBugs(board);
                    break;
                case 2:
                    getCrawler(board);
                    break;
                case 3:
                    board.tap();
                    displayBugs(board);
                    break;
                case 4:
                    displayBugsHistory(board);
                    break;
                case 5:
                    displayCells(board);
                    break;
                case 6:
                    runSimulation(board);
                    break;
                case 0:
                    cout << "Exiting..." << endl;
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
