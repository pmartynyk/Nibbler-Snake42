#include "Game.class.hpp"

Game::Game(int size) : _size(size)
{
}

Game::Game(Game const &val)
{
    *this = val;
}

Game &Game::operator=(Game const &val)
{
    if (this != &val)
    {
        this->_size = val._size;
    }
    return *this;
}

Game::~Game(void)
{
}

int Game::getSize(void)
{
    return this->_size;
}