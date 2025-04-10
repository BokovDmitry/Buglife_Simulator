#include "Bug.h"

#include "Direction.h"

const int WIDTH = 10;
const int HEIGHT = 10;

int Bug::getId() const { return this->id; }
Position Bug::getPosition() const { return this->position; }
Direction Bug::getDirection() const { return this->direction; }
int Bug::getSize() const { return this->size; }
bool Bug::getAlive() const { return this->alive; }
list<Position> Bug::getPath() const { return this->path; }

void Bug::setId(const int& id) { this->id = id; }
void Bug::setPosition(const Position& position) { this->position = position; }
void Bug::setDirection(const Direction& direction) { this->direction = direction; }
void Bug::setSize(const int& size) { this->size = size; }
void Bug::setAlive(const bool& alive) { this->alive = alive; }
void Bug::setPath(const list<Position>& path) { this->path = path; }

bool Bug::isWayBlocked() const {
    int x = this->getPosition().x;
    int y = this->getPosition().y;

    switch(this->getDirection()) {
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
