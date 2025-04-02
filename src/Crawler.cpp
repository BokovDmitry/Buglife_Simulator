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
int Crawler::getEatenBy() const {return this->eatenBy;}

void Crawler::setId(const int& id) {this->id = id;}
void Crawler::setSize(const int& size) {this->size = size;}
void Crawler::setPosition(const Position& position) {this->position = position;}
void Crawler::setDirection(const Direction& direction) {this->direction = direction;}
void Crawler::setAlive(const bool& alive) {this->alive = alive;}
void Crawler::setPath(const list<Position>& path) {this->path = path;}
void Crawler::setEatenBy(const int& id) {this->eatenBy = id;}

void Crawler::display() const {
    string alive = getAlive() ? "Alive" : "Dead";
    cout << right << "Crawler ID: " << this->getId() << setw(10) << " Size: " << this->getSize() <<
        setw(20) << " Position: {x: " << this->getPosition().x << ", y: " << this->getPosition().y << "}" <<
        setw(15) << " Direction: " << this->getDirection() <<setw(15) <<  " isAlive: " << alive << endl;

}

bool Crawler::isWayBlocked() const{
    int x = this->getPosition().x;
    int y = this->getPosition().y;
    Direction direction = this->getDirection();

    switch(direction) {
        case NORTH:
            return y==9;
        case SOUTH:
            return y==0;
        case EAST:
            return x==9;
        case WEST:
            return x==0;
        default:
            return false;
    }
}

void Crawler::move() {
    if(this->isWayBlocked()) {
        this->setDirection(static_cast<Direction>(1 + rand() % 4));
        this->move();
    }
    else {
        Position pos = this->getPosition();
        switch (this->getDirection()) {
            case NORTH: pos.y += 1; break;
            case SOUTH: pos.y -= 1; break;
            case EAST:  pos.x += 1; break;
            case WEST:  pos.x -= 1; break;
        }
        this->setPosition(pos);
        this->path.push_back(this->getPosition());
    }
}
