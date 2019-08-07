#include "../includes/Game.class.hpp"

Game::Game(int size) : _size(size), _endGame(false), _fps(5), _direction(down)
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
    clock_t t1;
    clock_t t2 = 0;
    selectLib();
    this->_snake.setData(this->_size / 2, this->_size / 2, 4);
    while (1)
    {
        t1 = clock() / (CLOCKS_PER_SEC / _fps);
        if (t1 > t2)
        {
            this->_library->draw(this->_snake, this->_direction, this->_size);
            this->_direction = this->_library->checkButton(this->_direction);
            t2 = clock() / (CLOCKS_PER_SEC / _fps);
        }
    }
}

void Game::selectLib(void)
{
    IDynamicLibrary *(*create)() = nullptr;
    this->_dl = dlopen("./ncurses/ncurses.so", RTLD_LAZY | RTLD_LOCAL);
    create = reinterpret_cast<IDynamicLibrary *(*)()>(dlsym(this->_dl, "createLib"));
    this->_library = create();
}
