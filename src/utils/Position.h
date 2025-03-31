#ifndef POSITION_H
#define POSITION_H

using namespace std;

struct Position {
    int x;
    int y;

    explicit Position(int x = 0, int y = 0):x(x), y(y) {}
};

#endif //POSITION_H
