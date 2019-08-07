#include "../includes/Food.class.hpp"

Food::Food(void): _x(0), _y(0), _alive(false) 
{
}

Food::Food(Food const &val)
{
    *this = val;
}

Food &Food::operator=(Food const &val)
{
    if (this != &val)
    {
        this->_x = val._x;
        this->_y = val._y;
        this->_alive = val._alive;
    }
    return *this;
}

Food::~Food(void)
{
}

int Food::getX(void)
{
    return this->_x;
}

int Food::getY(void)
{
    return this->_y;
}

bool Food::isAlive(void)
{
    return this->_alive;
}

void Food::setCord(int x, int y)
{
    this->_x = x;
    this->_y = y;
}

void Food::setAlive(bool alive)
{
    this->_alive = alive;
}