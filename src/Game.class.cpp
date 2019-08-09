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
        this->_food = val._food;
        this->_fps = val._fps;
        this->_direction = val._direction;
        this->_score_time = val._score_time;
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
    (void)_direction;
    clock_t t1;
    clock_t t2 = 0;
    selectLib();
    this->_snake.setData(this->_size / 2, this->_size / 2, 4);
    srand((int)time(0));
    while (!this->_endGame)
    {
        this->_direction = this->_library->checkButton(this->_direction, this->_endGame);
        t1 = clock() / (CLOCKS_PER_SEC / _fps);
        if (t1 > t2)
        {
            
            this->_library->draw(this->_snake, this->_direction, this->_size, this->_endGame, this->_food, this->_score_time);
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


// Direction Game::checkButton(Direction direction, bool &endGame)
// {
//     int c;

//     c = getch();
//     if (c == KEY_DOWN && direction != up)
//         return down;
//     else if (c == KEY_UP && direction != down)
//         return up;
//     else if (c == KEY_LEFT && direction != right)
//         return left;
//     else if (c == KEY_RIGHT && direction != left)
//         return right;
//     else if (c == 27)
//         endGame = true;
//     return direction;
// }