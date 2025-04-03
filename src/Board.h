#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>

#include "Crawler.h"

using namespace std;

class Board {
    const int width = WIDTH;
    const int height = HEIGHT;
    vector<Crawler*> crawlers;
    vector<Crawler*> deadCrawlers;
    vector<Crawler* > cells[100];

public:
    explicit Board(vector<Crawler*> crawlers);
    Board();
    ~Board();

    vector<Crawler*> getCrawlers() const;
    void setCrawlers(vector<Crawler*> crawlers);

    void initializeBoard(const string& fileName);

    void displayBugs() const;

    Crawler* getCrawler(const int& id) const;

    void tap();

    void displayLifeHistory() const;

    void displayCells() const;

    void resetCells();

    void fight();

    void runSimulation();
};

#endif //BOARD_H
