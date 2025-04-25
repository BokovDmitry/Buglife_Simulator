#include "Knightcrawler.h"

Knightcrawler::Knightcrawler() = default;
Knightcrawler::Knightcrawler(int id, int size, Position position, Direction direction) {
    this->id = id;
    this->size = size;
    this->position = position;
    this->direction = direction;
    this->setAlive(true);
    this->setEatenBy(-1);
}

void Knightcrawler::display() {
    const string alive = getAlive() ? "Alive" : "Dead";
    cout << left
         << "Knightcrawler ID: " << setw(6) << this->getId()
         << "Size: " << setw(8) << this->getSize()
         << "Position: {x: " << this->getPosition().x << ", y: " << this->getPosition().y << "}    "
         << "Direction: " << setw(6) << this->getDirection()
         << "isAlive: " << alive << endl;
}

bool Knightcrawler::isWayHalfBlocked(){
    int x = this->getPosition().x;
    int y = this->getPosition().y;

    switch(this->getDirection()) {
        case NORTH:
            return y>HEIGHT-2 || x==9;
        case SOUTH:
            return y<2 || x==0;
        case EAST:
            return x>WIDTH-2 || y==0;
        case WEST:
            return x<2 || y==9;
    }
    return false;
}

void Knightcrawler::move() {
    Position pos = this->position;

    // if (this->isWayBlocked()) {
    //     for (int i = 0; i < 4; i++) {
    //         auto newDir = static_cast<Direction>(1 + rand() % 4);
    //         this->setDirection(newDir);
    //         if (!this->isWayBlocked()) {
    //             break;
    //         }
    //     }
    // }
    while(this->isWayBlocked()) {
        auto newDir = static_cast<Direction>(1 + rand() % 4);
        this->setDirection(newDir);
    }

    if (this->isWayHalfBlocked()) {
        switch (this->getDirection()) {
            case NORTH: pos.y += 2; break;
            case SOUTH: pos.y -=2; break;
            case EAST:  pos.x +=2; break;
            case WEST:  pos.x -= 2; break;
        }
    } else {
        switch (this->getDirection()) {
            case NORTH: pos.y += 2; pos.x++; break;
            case SOUTH: pos.y -= 2; pos.x--; break;
            case EAST:  pos.x += 2; pos.y--; break;
            case WEST:  pos.x -= 2; pos.y++; break;
        }
    }

    if (pos.x < 0) pos.x = 0;
    if (pos.y < 0) pos.y = 0;
    if (pos.x >= WIDTH) pos.x = WIDTH - 1;
    if (pos.y >= HEIGHT) pos.y = HEIGHT - 1;

    this->setPosition(pos);
    this->path.push_back(this->getPosition());
}




