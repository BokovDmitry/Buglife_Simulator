#include "Board.h"

#include "Knightcrawler.h"

Board::Board(vector<Bug*> crawlers):crawlers(move(crawlers)) {
};

Board::Board() {
}

Board::~Board() {
    for (Bug* crawler : crawlers) {
        delete crawler;
    }
}

void Board::resetCells() {
    for(int x = 0; x < (WIDTH*HEIGHT); x++) {
        cells[x].clear();
    }
}

vector<Bug*> Board::getCrawlers() const {
    return crawlers;
}

Bug* parseCrawler(const string& line) {
    Bug* bug = nullptr;
    string temp = "";
    Position pos = Position();
    stringstream ss(line);
    getline(ss, temp, ',');

    switch (temp[0]) {
        case 'C': bug = new Crawler(); break;
        case 'K': bug = new Knightcrawler(); break;
        default: break;
    }

    getline(ss, temp, ',');
    bug->setId(stoi(temp));
    getline(ss, temp, ',');
    pos.x = stoi(temp);
    getline(ss, temp, ',');
    pos.y = stoi(temp);
    bug->setPosition(pos);
    getline(ss, temp, ',');
    const auto dir = static_cast<Direction>(stoi(temp));
    bug->setDirection(dir);
    getline(ss, temp, ',');
    bug->setSize(stoi(temp));

    return bug;
}

void Board::initializeBoard(const string& filename) {
    ifstream file(filename);
    if(file) {
        string line;
        while(!file.eof()) {
            getline(file, line);
            Bug *bug = parseCrawler(line);
            crawlers.push_back(bug);
            cells[bug->getOnboardPosition()].push_back(bug);
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

Bug* Board::getCrawler(const int& id) const {
    for(auto& crawler : crawlers) {
        if(crawler->getId() == id) {
            return crawler;
        }
    }
    return nullptr;
}

void Board::tap() {
    resetCells();
    for(auto& crawler : crawlers) {
        if(crawler->getAlive()) {
            crawler->move();
            const int pos = crawler->getOnboardPosition();
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
        for(const auto& step : crawler->getPath()) {
            cout << "(" << step.x << "," << step.y << ")";
        }
        cout << endl;
        if (!crawler->getAlive()) {
            cout << "Eaten by: " << crawler->getEatenBy() << endl;
        }
        cout << endl;
    }
}

void Board::displayCells() const{
    for(auto i = 0; i < size(cells); i++) {
        cout << "Cell {X: " << (i%WIDTH) <<", Y: " << (i/WIDTH) << "} - ";
        if(!cells[i].empty()) {
            cout << "Bugs: " << endl;
            for(auto& crawler : cells[i]) {
                if(crawler->getAlive())
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
            cout <<"On cell (" << i%WIDTH << ", " << i/WIDTH << ") between ";
            Bug* winner = nullptr;
            vector<Bug*> temp = {};
            int total_size = 0;
            for(const auto& crawler : cells[i]) {
                if (temp.empty() || crawler->getSize() > temp[0]->getSize()) {
                    temp.clear();
                    temp.push_back(crawler);
                }else if(!temp.empty() && crawler->getSize() == temp[0]->getSize()) {
                    temp.push_back(crawler);
                }
                total_size += crawler->getSize();
                cout << crawler->getId() << " ";
            }
            winner = temp[rand()%temp.size()];

            if(winner != nullptr) {
                cout << endl << winner->getId() << " have won!" << endl;
                winner->setSize(total_size);
                for(const auto& crawler : cells[i]) {
                    if(crawler != winner) {
                        crawler->setAlive(false);
                        crawler->setEatenBy(winner->getId());
                        deadCrawlers.push_back(crawler);
                    }
                }
            }
            cout << endl;
        }
    }
}

void Board::writeToFile(const string &fileName) const {
    ofstream out(fileName);
    if(out) {
        for(auto crawler : crawlers) {
            out << crawler -> getId() << " :";
            for(auto& pos : crawler->getPath()) {
                out << " (" << pos.x << ", " << pos.y << ")";
            }
            if(crawler->getEatenBy() != -1)
                out << " Eaten By: " << crawler->getEatenBy() << endl;
            else
                out << endl;
        }
        cout << "Life history successfully written to " << fileName << endl;
    } else {
        cout << "File could not be opened" << endl;
    }

}


void Board::runSimulation() {
    while(deadCrawlers.size() != crawlers.size()-1) {
        tap();
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    cout << "Simulation complete" << endl;
    displayBugs();
}

