#ifndef JUMPER_H
#define JUMPER_H
#include "utils/Bug.h"
#include "utils/Direction.h"
#include "utils/Position.h"

#include <iostream>
#include <iomanip>
#include <random>

using namespace std;

class Hopper : public Bug {
    int hopLength;

public:
    Hopper(int hopLength);
    Hopper(int id, int size, Position position, Direction direction, int hopLength);

    int getHopLength() const;

    void setHopLength(int length);

    void display() override;

    void move() override;
};

#endif //JUMPER_H