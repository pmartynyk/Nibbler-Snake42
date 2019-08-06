#ifndef UNIT_CLASS_HPP
#define UNIT_CLASS_HPP

#include <iostream>

class Unit
{
private:
    int _x;
    int _y;
    bool _head;

public:
    Unit(int x, int y);
    Unit(Unit const &val);
    Unit &operator=(Unit const &val);
    ~Unit(void);
    void setHead(void);

    int getX(void);
    int getY(void);
};

#endif