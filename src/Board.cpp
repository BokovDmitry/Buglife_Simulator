#include "Board.h"

Board::Board(vector<Crawler*> crawlers):crawlers(move(crawlers)) {
    srand(time(0));
};

Board::Board() {
    srand(time(0));
}

Board::~Board() {
    for (Crawler* crawler : crawlers) {
        delete crawler;  // Free allocated memory
    }
}

void Board::resetCells() {
    for(int x = 0; x < 100; x++) {
        cells[x].clear();  // Clear each cell
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
            cells[crawler->getPosition().y*10+crawler->getPosition().x].push_back(crawler);
        }
    } else {
        cout << "File could not be opened" << endl;
    }
}

void Board::displayBugs() const {
    for(auto& crawler : crawlers) {
        crawler->display();
    }
}

Crawler* Board::getCrawler(const int& id) const {
    for(auto& crawler : crawlers) {
        if(crawler->getId() == id) {
            return crawler;
        }
    }
    return nullptr;
}

void Board::setCrawlers(vector<Crawler *> crawlers) {
    this->crawlers = move(crawlers);
}

void Board::tap() {
    resetCells();
    for(auto& crawler : crawlers) {
        if(crawler->getAlive()) {
            crawler->move();
            int pos = crawler->getPosition().y*10+crawler->getPosition().x;
            cells[pos].push_back(crawler);
        }
    }
    fight();
}

void Board::displayLifeHistory() const {
    for(auto& crawler : crawlers) {
        cout << "Details: ";
        crawler->display();
        cout << "Path: ";
        for(const auto& way : crawler->getPath()) {
            cout << "(" << way.x << "," << way.y << ")";
        }
        cout << endl;
        cout << endl;
    }
}

void Board::displayCells() const{
    for(auto i = 0; i < size(cells); i++) {
        cout << "Cell {X: " << (i%10) <<", Y: " << (i/10) << "} - ";
        if(!cells[i].empty()) {
            cout << "Bugs: " << endl;
            for(auto& crawler : cells[i]) {
                crawler->display();
            }
        }
        else
        {
            cout << "Cell is empty" << endl;
        }
    }
}

void Board::fight() {
    for(auto i = 0; i < std::size(cells); i++) {
        if(cells[i].size() > 1) {
            cout << "FIGHT!" << endl;
            cout <<"On cell (" << i%10 << ", " << i/10 << ") between ";
            Crawler* winner = nullptr;
            int total_size = 0;
            for(const auto& crawler : cells[i]) {
                if (winner == nullptr || crawler->getSize() > winner->getSize()) {
                    winner = crawler;
                }
                total_size += crawler->getSize();
                cout << crawler->getId() << " ";
            }
            if(winner != nullptr) {
                cout << endl << winner->getId() << " have won!" << endl;
                winner->setSize(total_size);
                for(const auto& crawler : cells[i]) {
                    if(crawler != winner) {
                        crawler->setAlive(false);
                        deadCrawlers.push_back(crawler);
                    }
                }
            }
            cout << endl;
        }
    }
}

void Board::runSimulation() {
    while(deadCrawlers.size() != crawlers.size()-1) {
        tap();
        // displayBugs();
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    cout << "Simulation complete" << endl;
    displayBugs();
}

