#include "../includes/Unit.class.hpp"

Unit::Unit(int x, int y) : _x(x), _y(y), _head(false)
{
    // std::cout << _x << "  ok" << _y << std::endl;
}

Unit::Unit(Unit const &val)
{
    *this = val;
}

Unit &Unit::operator=(Unit const &val)
{
    if (this != &val)
    {
        this->_x = val._x;
        this->_y = val._y;
        this->_head = val._head;
    }
    return *this;
}

Unit::~Unit(void)
{
}

void Unit::setHead(void)
{
    this->_head = true;
}

int Unit::getX(void)
{
    return this->_x;
}

int Unit::getY(void)
{
    return this->_y;
}

// int Unit::getPrevX(void)
// {
//     return this->_prevx;
// }

// int Unit::getPrevY(void)
// {
//     return this->_prevy;
// }

bool Unit::isHead(void)
{
    return this->_head;
}

void Unit::setX(int x)
{
    this->_x = x;
}

void Unit::setY(int y)
{
    this->_y = y;
}

// void Unit::setPrevX(int x)
// {
//     this->_prevx = x;
// }

// void Unit::setPrevY(int y)
// {
//     this->_prevy = y;
// }