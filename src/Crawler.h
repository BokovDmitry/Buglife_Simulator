#ifndef CRAWLER_H
#define CRAWLER_H

#include <iostream>
#include <list>

#include "utils/Bug.h"
#include "utils/Position.h"
#include "utils/Direction.h"

using namespace std;

extern const int WIDTH;
extern const int HEIGHT;

class Crawler: public Bug {

public:
    Crawler();
    Crawler(int id, string type, int size, Position position, Direction direction);

    void display() override;

    void move() override;
};

#endif //CRAWLER_H