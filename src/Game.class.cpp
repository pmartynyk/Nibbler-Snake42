#include "../includes/Game.class.hpp"

Game::Game(int size) : _size(size), _endGame(false)
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
        this->_endGame = val._endGame;
        this->_snake = val._snake;
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
    selectLib();
    // this->_library->DrowMap(this->_size);
    this->_snake.setData(this->_size / 2, this->_size / 2);
    // std::cout << this->
    // while (1)
    // {
    //     // if ()
    //     this->_library->DrowMap(this->_size);
    
        this->_library->DrawSnake(this->_snake);
    // }
}

void Game::selectLib(void)
{
    IDynamicLibrary *(*create)() = nullptr;
    this->_dl = dlopen("./ncurses/ncurses.so", RTLD_LAZY | RTLD_LOCAL);
    create = reinterpret_cast<IDynamicLibrary *(*)()>(dlsym(this->_dl, "createLib"));
    this->_library = create();
}
