#include "../includes/Snake.class.hpp"
// #include "../includes/Unit.class.hpp"

Snake::Snake(void)
{
    this->_length = 4;
}

Snake::Snake(Snake const &val)
{
    *this = val;
}

Snake &Snake::operator=(Snake const &val)
{
    if (this != &val)
    {
        this->_x = val._x;
        this->_y = val._y;
        this->_length = val._length;
        this->_units = val._units;
    }
    return *this;
}

Snake::~Snake(void)
{
}

void Snake::setData(int x, int y)
{
    this->_x = x;
    this->_y = y;
    int i = 0;
    // while (i < length)
    // {
    //     this->_units.push_back(new Unit(x, y - i));
    //     // this->_units.front()->setHead();
    //     // std::cout << this->_units << std::endl;
    //     i++;
    // }
    this->_length = i;
}

std::list<Unit *> &Snake::getUnits(void)
{
    return this->_units;
}

int Snake::getLength(void)
{
    return this->_length;
}

// Snake *Snake::operator&()
// {
//     return this;
// }

// Snake const *Snake::operator&() const
// {
//     return this;
// }
