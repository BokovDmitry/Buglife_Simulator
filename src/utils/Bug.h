#ifndef BUG_H
#define BUG_H
#include <list>

#include "Direction.h"
#include "Position.h"
#include <string>

extern const int WIDTH;
extern const int HEIGHT;

using namespace std;

class Bug {
protected:
    int id = 0;
    string type;
    Position position;
    Direction direction;
    int size = 0;
    bool alive = true;
    list<Position> path;
    int eatenBy = -1;

public:
    virtual ~Bug() = default;

    virtual void move() = 0;

    virtual void display() = 0;

    int getOnboardPosition() const;

    bool isWayBlocked() const;

    int getId() const;
    void setId(const int& id);
    string getType() const;
    void setType(const string& type);
    Position getPosition() const;
    void setPosition(const Position& position);
    Direction getDirection() const;
    void setDirection(const Direction& direction);
    int getSize() const;
    void setSize(const int& size);
    bool getAlive() const;
    void setAlive(const bool& alive);
    const list<Position>& getPath() const;
    std::list<Position>& getPath();
    void setPath(const list<Position>& path);
    int getEatenBy() const;
    void setEatenBy(const int& eatenBy);
};

#endif