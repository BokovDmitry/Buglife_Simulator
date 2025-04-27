#include "SuperBug.h"

SuperBug::SuperBug() = default;
SuperBug::SuperBug(int id, string type, int size, Position position, Direction direction) {
    this->setId(id);
    this->setType(type);
    this->setSize(size);
    this->setPosition(position);
    this->setDirection(direction);
    this->setAlive(true);
    this->setEatenBy(-1);
}

void SuperBug::display() {
    const string alive = getAlive() ? "Alive" : "Dead";
    cout << left
         << "SuperBug ID: " << setw(6) << this->getId()
         << "Size: " << setw(8) << this->getSize()
         << "Position: {x: " << this->getPosition().x << ", y: " << this->getPosition().y << "}    "
         << "Direction: " << setw(6) << this->getDirection()
         << "isAlive: " << alive << endl;
}

void SuperBug::move() {
    this->path.push_front(this->getPosition());
}