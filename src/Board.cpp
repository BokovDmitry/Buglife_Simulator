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

void parseCrawler(Crawler& crawler, const string& line) {
    string temp = "";
    Position pos = Position();
    stringstream ss(line);
    getline(ss, temp, ',');
    getline(ss, temp, ',');
    crawler.setId(stoi(temp));
    getline(ss, temp, ',');
    pos.x = stoi(temp);
    getline(ss, temp, ',');
    pos.y = stoi(temp);
    crawler.setPosition(pos);
    getline(ss, temp, ',');
    const auto dir = static_cast<Direction>(stoi(temp));
    crawler.setDirection(dir);
    getline(ss, temp, ',');
    crawler.setSize(stoi(temp));
}

void Board::initializeBoard(const string& filename) {
    ifstream file(filename);
    if(file) {
        string line;
        while(!file.eof()) {
            getline(file, line);
            auto *crawler = new Crawler();
            parseCrawler(*crawler, line);
            crawlers.push_back(crawler);
            cells[crawler->getPosition().x][crawler->getPosition().y].push_back(crawler);
        }
    } else {
        cout << "File could not be opened" << endl;
    }
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

