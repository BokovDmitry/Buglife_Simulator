#include "Hopper.h"

Hopper::Hopper(int hopLength): hopLength(hopLength) {};
Hopper::Hopper(int id, string type, int size, Position position, Direction direction, int hopLength){
    this->id = id;
    this->type = type;
    this->size = size;
    this->position = position;
    this->direction = direction;
    this->setAlive(true);
    this->setEatenBy(-1);
    this->setHopLength(hopLength);
}

int Hopper::getHopLength() const { return this->hopLength;}

void Hopper::setHopLength(int length){ this -> hopLength = length;}


void Hopper::display() {
    const string alive = getAlive() ? "Alive" : "Dead";
    cout << left
         << "Hopper ID: " << setw(6) << this->getId()
         << "Size: " << setw(8) << this->getSize()
         << "Position: {x: " << this->getPosition().x << ", y: " << this->getPosition().y << "}    "
         << "Direction: " << setw(6) << this->getDirection()
         << "Hop Length: " << setw(8) << this->getHopLength()
         << "isAlive: " << alive << endl;
}

void Hopper::move() {
    while(isWayBlocked()) {
        auto newDir = static_cast<Direction>(1 + rand() % 4);
        this->setDirection(newDir);
        if (!this->isWayBlocked()) {
            break;
        }
    }
    Position pos = this->getPosition();
    switch (this->getDirection()) {
        case NORTH: pos.y += this->getHopLength(); break;
        case SOUTH: pos.y -= this->getHopLength(); break;
        case EAST:  pos.x += this->getHopLength(); break;
        case WEST:  pos.x -= this->getHopLength(); break;
    }

    if (pos.x < 0) pos.x = 0;
    if (pos.y < 0) pos.y = 0;
    if (pos.x >= WIDTH) pos.x = WIDTH - 1;
    if (pos.y >= HEIGHT) pos.y = HEIGHT - 1;

    this->setPosition(pos);
    this->path.push_back(this->getPosition());
}