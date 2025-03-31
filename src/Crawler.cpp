#include "Crawler.h"

#include <iomanip>

Crawler::Crawler(){}

Crawler::Crawler(int id, int size, Position position, Direction direction)
    : id(id), size(size), position(position), direction(direction){}

int Crawler::getId() const {return this->id;}
int Crawler::getSize() const {return this->size;}
Position Crawler::getPosition() const {return this->position;}
Direction Crawler::getDirection() const {return this->direction;}
bool Crawler::getAlive() const {return this->alive;}
list<Position> Crawler::getPath() const {return this->path;}

void Crawler::setId(const int& id) {this->id = id;}
void Crawler::setSize(const int& size) {this->size = size;}
void Crawler::setPosition(const Position& position) {this->position = position;}
void Crawler::setDirection(const Direction& direction) {this->direction = direction;}
void Crawler::setAlive(const bool& alive) {this->alive = alive;}
void Crawler::setPath(const list<Position>& path) {this->path = path;}

void Crawler::display() const {
    string alive = getAlive() ? "Alive" : "Dead";
    cout << right << "Crawler ID: " << this->getId() << setw(10) << " Size: " << this->getSize() <<
        setw(20) << " Position: {x: " << this->getPosition().x << ", y: " << this->getPosition().y << "}" <<
        setw(15) << " Direction: " << this->getDirection() <<setw(15) <<  " isAlive: " << alive << endl;

}

bool Crawler::isWayBlocked() const {
}

void Crawler::move() {
}
