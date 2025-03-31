#include "Board.h"

Board::Board(vector<Crawler*> crawlers):crawlers(move(crawlers)), cells(10, vector<vector<Crawler*>>(10)) {
    srand(time(0));
};

Board::Board() : cells(10, vector<vector<Crawler*>>(10)) {
    srand(time(0));
}

Board::~Board() {
    for (Crawler* crawler : crawlers) {
        delete crawler;  // Free allocated memory
    }
}

void Board::resetCells() {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            cells[x][y].clear();  // Clear each cell
        }
    }
}

vector<Crawler*> Board::getCrawlers() const {}

void Board::initializeBoard(const string &fileName) {

}

void Board::displayBugs() const {

}

void Board::setCrawlers(vector<Crawler *> crawlers) {
}

Crawler * Board::getCrawler(const int &id) const {
}

void Board::tap() {
}

void Board::displayLifeHistory() const {
}

void Board::displayCells() const {
}

void Board::fight() {
}

