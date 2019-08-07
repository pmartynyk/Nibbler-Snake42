#ifndef SNAKE_CLASS_HPP
#define SNAKE_CLASS_HPP

#include <list>
#include <iostream>
#include "Unit.class.hpp"

class Unit;

class Snake
{
private:
    int _length;
    int _x;
    int _y;
    std::list<Unit*> _units;

public:
    Snake(void);
    Snake(Snake const &val);
    Snake &operator=(Snake const &val);
    ~Snake(void);

    void setData(int x, int y, int length);
    std::list<Unit*> &getUnits(void);
    void addUnit(void);

    int getLength(void);
};

#endif