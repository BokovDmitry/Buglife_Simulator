#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "Crawler.h"

using namespace std;

class Board {
    const int width = 10;
    const int height = 10;
    vector<Crawler*> crawlers;
    vector<vector<vector<Crawler*>>> cells;

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
};

#endif //BOARD_H
