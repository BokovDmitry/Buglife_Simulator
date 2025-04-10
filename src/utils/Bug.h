#ifndef BUG_H
#define BUG_H
#include <list>

#include "Direction.h"
#include "Position.h"

extern const int WIDTH;
extern const int HEIGHT;

class Bug {
    int id = 0;
    Position position;
    Direction direction;
    int size = 0;
    bool alive = true;
    list<Position> path;

    virtual void move() = 0;

    bool isWayBlocked() const;

public:
    int getId() const;

    void setId(const int& id);

    Position getPosition() const;

    void setPosition(const Position& position);

    Direction getDirection() const;

    void setDirection(const Direction& direction);

    int getSize() const;

    void setSize(const int& size);

    bool getAlive() const;

    void setAlive(const bool& alive);

    list<Position> getPath() const;

    void setPath(const list<Position>& path);
};

#endif
