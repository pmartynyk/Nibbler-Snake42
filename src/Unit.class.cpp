#include "../includes/Unit.class.hpp"

Unit::Unit(int x, int y) : _x(x), _y(y), _head(false)
{
    std::cout << _x << "  ok" << _y << std::endl;
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