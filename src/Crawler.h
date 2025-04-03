
#ifndef CRAWLER_H
#define CRAWLER_H

#include <iostream>
#include <list>
#include "utils/Position.h"
#include "utils/Direction.h"

using namespace std;

extern const int WIDTH;
extern const int HEIGHT;

class Crawler {
    int id;
    int size;
    Position position;
    Direction direction;
    bool alive = true;
    list<Position> path = {};
    int eatenBy = -1;

public:
    Crawler();
    Crawler(int id, int size, Position position, Direction direction);

    int getId() const;
    int getSize() const;
    bool getAlive() const;
    list<Position> getPath() const;
    Position getPosition() const;
    Direction getDirection() const;
    int getEatenBy() const;
    int getOnboardPosition() const;

    void setId(const int& id);
    void setSize(const int& size);
    void setAlive(const bool& alive);
    void setPosition(const Position& position);
    void setDirection(const Direction& direction);
    void setPath(const list<Position>& path);
    void setEatenBy(const int& id);

    void display() const;

    bool isWayBlocked() const;

    void move();
};

#endif //CRAWLER_H
