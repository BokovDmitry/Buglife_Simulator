#include "Crawler.h"

#include <iomanip>

const int WIDTH = 10;
const int HEIGHT = 10;

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
int Crawler::getOnboardPosition() const {return this->position.y*WIDTH+this->position.x;}

void Crawler::setId(const int& id) {this->id = id;}
void Crawler::setSize(const int& size) {this->size = size;}
void Crawler::setPosition(const Position& position) {this->position = position;}
void Crawler::setDirection(const Direction& direction) {this->direction = direction;}
void Crawler::setAlive(const bool& alive) {this->alive = alive;}
void Crawler::setPath(const list<Position>& path) {this->path = path;}
void Crawler::setEatenBy(const int& id) {this->eatenBy = id;}

void Crawler::display() const {
    string alive = getAlive() ? "Alive" : "Dead";
    cout << left
         << "Crawler ID: " << setw(6) << this->getId()
         << "Size: " << setw(8) << this->getSize()
         << "Position: {x: " << this->getPosition().x << ", y: " << this->getPosition().y << "}    "
         << "Direction: " << setw(6) << this->getDirection()
         << "isAlive: " << alive << endl;

}

bool Crawler::isWayBlocked() const{
    int x = this->getPosition().x;
    int y = this->getPosition().y;
    Direction direction = this->getDirection();

    switch(direction) {
        case NORTH:
            return y==HEIGHT-1;
        case SOUTH:
            return y==0;
        case EAST:
            return x==WIDTH-1;
        case WEST:
            return x==0;
    }
    return false;
}

void Crawler::move() {
    if (this->isWayBlocked()) {
        for (int i = 0; i < 4; i++) {
            auto newDir = static_cast<Direction>(1 + rand() % 4);
            this->setDirection(newDir);
            if (!this->isWayBlocked()) {
                break;
            }
        }
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
