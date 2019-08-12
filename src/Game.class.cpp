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
            Logic().logic(this->_snake, this->_food, this->_direction, this->_endGame, this->_size, this->_score_time, this->_music);
            this->_library->draw(this->_snake, this->_size, this->_food, this->_score_time, this->_endGame);
            t2 = clock() / (CLOCKS_PER_SEC / _fps);
        }
    }
}

void Game::setMusic(void)
{
    IMusic *(*create)() = nullptr;
    this->_dl = dlopen("./music/music.so", RTLD_LAZY | RTLD_LOCAL);

    if (!this->_dl)
    {
        std::cerr << "open_lib: dlopen : " << dlerror() << std::endl;
        throw std::exception();
    }
    if ((create = reinterpret_cast<IMusic *(*)()>(dlsym(this->_dl, "createLib"))) == NULL)
    {
        std::cerr << "open_lib: dlsym : " << dlerror() << std::endl;
        throw std::exception();
    }
    this->_music = create();
}

void Game::selectLib(void)
{
    IDynamicLibrary *(*create)() = nullptr;
    this->_dl = dlopen("./ncurses/ncurses.so", RTLD_LAZY | RTLD_LOCAL);
    // this->_dl = dlopen("./SDLlib/SDLlib.so", RTLD_LAZY | RTLD_LOCAL);
    // create = reinterpret_cast<IDynamicLibrary *(*)()>(dlsym(this->_dl, "createLib"));

    if (!this->_dl)
    {
        std::cerr << "open_lib: dlopen : " << dlerror() << std::endl;
        throw std::exception();
    }
    if ((create = reinterpret_cast<IDynamicLibrary *(*)()>(dlsym(this->_dl, "createLib"))) == NULL)
    {
        std::cerr << "open_lib: dlsym : " << dlerror() << std::endl;
        throw std::exception();
    }
    this->_library = create();
}
