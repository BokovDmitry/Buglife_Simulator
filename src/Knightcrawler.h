#ifndef KNIGHTCRAWLER_H
#define KNIGHTCRAWLER_H

#include "utils/Bug.h"
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class Knightcrawler : public Bug {

    bool isWayHalfBlocked();

public:
    Knightcrawler();

    Knightcrawler(int id, int size, Position position, Direction direction);

    void display() override;

    void move() override;
};


#endif //KNIGHTCRAWLER_H
