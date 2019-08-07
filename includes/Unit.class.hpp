#ifndef UNIT_CLASS_HPP
#define UNIT_CLASS_HPP

#include <iostream>

class Unit
{
private:
    int _x;
    int _y;
    // int _prevx;
    // int _prevy;
    bool _head;

public:
    Unit(int x, int y);
    Unit(Unit const &val);
    Unit &operator=(Unit const &val);
    ~Unit(void);
    void setHead(void);

    int getX(void);
    int getY(void);
    // int getPrevX(void);
    // int getPrevY(void);

    bool isHead(void);

    void setX(int);
    void setY(int);
    // void setPrevX(int);
    // void setPrevY(int);
};

#endif