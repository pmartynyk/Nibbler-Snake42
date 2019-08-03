#include "../includes/Game.class.hpp"

Game::Game(int size) : _size(size)
{
    this->_library = new Ncurses;
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

void Game::play(void)
{
    while (1)
    {
        // std::cout << "ko" << std::endl;
        this->_library->DrowMap(this->_size);
    }
}