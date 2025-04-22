#include "Board.h"

#include <SFML/Graphics.hpp>

#include "Knightcrawler.h"

using namespace std;
using namespace sf;

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

void Board::initBoard(const string& filename) {

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

void Board::runGUI() {
    //Window Initializing
    constexpr int wWidth = 600;
    constexpr int wHeight = 600;
    RenderWindow window(VideoMode(wWidth, wHeight), "My Bug Project");

    vector<RectangleShape> squares;

    //Creating a Board
    for (int row = 0; row < 10; row++) {
        for (int col = 0; col < 10; col++) {
            RectangleShape square(Vector2f(wWidth/WIDTH, wHeight/HEIGHT));
            square.setFillColor(Color::White );
            square.setOutlineThickness(3.0f);
            square.setOutlineColor(Color::Black);

            square.setPosition(Vector2f(static_cast<float>(row)*60, static_cast<float>(col)*60 ));  // top left hand corner of square

            squares.push_back(square);
        }
    }

    window.setFramerateLimit(60);

    while (window.isOpen() && deadCrawlers.size() != crawlers.size()-1) {
        Event event{};
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        window.clear();

        for (RectangleShape &square: squares) {
            window.draw(square);
        }

        for (auto bug : crawlers) {
            if(bug->getAlive()) {
                Sprite bugSprite;
                Texture imageTexture;

                if(typeid(*bug) == typeid(Crawler))
                    imageTexture.loadFromFile("./src/img/bug.png");
                else if(typeid(*bug) == typeid(Knightcrawler))
                    imageTexture.loadFromFile("./src/img/knight.png");

                bugSprite.setTexture(imageTexture);
                bugSprite.setScale((wWidth/WIDTH) / bugSprite.getGlobalBounds().width, (wHeight/HEIGHT) / bugSprite.getGlobalBounds().height);
                bugSprite.setPosition(Vector2f(static_cast<float>(bug->getPosition().x)*60, static_cast<float>(bug->getPosition().y)*60 ));
                window.draw(bugSprite);
            }
        }

        tap();
        this_thread::sleep_for(chrono::milliseconds(100));

        window.display();
    }
}


