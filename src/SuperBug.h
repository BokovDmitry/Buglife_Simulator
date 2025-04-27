#ifndef SUPERBUG_H
#define SUPERBUG_H
#include "utils/Bug.h"
#include <iostream>
#include <string>
#include <iomanip>


using namespace std;

class SuperBug : public Bug{
public:
    SuperBug();
    SuperBug(int id, string type, int size, Position position, Direction direction);

    void display() override;
    void move() override;
};

#endif //SUPERBUG_H