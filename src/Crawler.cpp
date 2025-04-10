#include "Crawler.h"

#include <iomanip>

const int WIDTH = 10;
const int HEIGHT = 10;

Crawler::Crawler(){}

Crawler::Crawler(int id, int size, Position position, Direction direction) {
    this->setId(id);
    this->setSize(size);
    this->setPosition(position);
    this->setDirection(direction);
    this->setAlive(true);
    this->setEatenBy(-1);
}

void Crawler::display() {
    const string alive = getAlive() ? "Alive" : "Dead";
    cout << left
         << "Crawler ID: " << setw(6) << this->getId()
         << "Size: " << setw(8) << this->getSize()
         << "Position: {x: " << this->getPosition().x << ", y: " << this->getPosition().y << "}    "
         << "Direction: " << setw(6) << this->getDirection()
         << "isAlive: " << alive << endl;

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
