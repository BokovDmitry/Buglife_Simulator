#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>
#include <ctime>

#include "Crawler.h"

using namespace std;

class Board {
    const int width = WIDTH;
    const int height = HEIGHT;
    vector<Bug*> crawlers;
    vector<Bug*> deadCrawlers;
    vector<Bug*> cells[100];

public:
    explicit Board(vector<Bug*> crawlers);
    Board();
    ~Board();

    vector<Bug*> getCrawlers() const;
    void setCrawlers(vector<Bug*> crawlers);

    void initBoard(const string& fileName);

    void displayBugs() const;

    Bug* getCrawler(const int& id) const;

    void tap();

    void displayLifeHistory() const;

    void displayCells() const;

    void resetCells();

    void fight();

    void runSimulation();

    void writeToFile(const string& fileName) const;

    void runGUI();
};

#endif //BOARD_H
