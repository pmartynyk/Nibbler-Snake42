#include "../includes/Game.class.hpp"

Game::Game(int size) : _size(size), _library(nullptr), _endGame(false), _fps(5), _direction(down), _event(ncurses), _changeLibrary(false), _move(true)
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
    clock_t t1;
    clock_t t2 = 0;
    setMusic();
    selectLib();
    this->_snake.setData(this->_size / 2, this->_size / 2, 4);
    srand((int)time(0));
    while (!this->_endGame)
    {
        this->_direction = this->_library->checkButton(this->_direction, this->_endGame, this->_event, this->_changeLibrary, this->_move);
        t1 = clock() / (CLOCKS_PER_SEC / _fps);
        if (t1 > t2 || this->_endGame)
        {
            if (this->_changeLibrary)
                selectLib();
            if (!this->_endGame && this->_event != stop)
                Logic().logic(this->_snake, this->_food, this->_direction, this->_endGame, this->_size, this->_score_time, this->_music, this->_fps);
            this->_library->draw(this->_snake, this->_size, this->_food, this->_score_time, this->_endGame);
            t2 = clock() / (CLOCKS_PER_SEC / _fps);
            this->_move = true;
            
        }
    }
}

void Game::setMusic(void)
{
    IMusic *(*create)() = nullptr;
    this->_dlMus = dlopen("./music/music.so", RTLD_LAZY | RTLD_LOCAL);

    if (this->_dlMus == nullptr)
    {
        std::cerr << "open_lib: dlopen : " << dlerror() << std::endl;
        throw std::exception();
    }
    if ((create = reinterpret_cast<IMusic *(*)()>(dlsym(this->_dlMus, "create"))) == NULL)
    {
        std::cerr << "open_lib: dlsym : " << dlerror() << std::endl;
        throw std::exception();
    }
    this->_music = create();
}

void Game::selectLib()
{
    IDynamicLibrary *(*create)() = nullptr;

    if (this->_library != nullptr)
    {
        this->_event = stop;
        delete(this->_library);
    }        

    if (this->_event == ncurses)
        this->_dl = dlopen("./ncurses/ncurses.so", RTLD_LAZY | RTLD_LOCAL);
    else if (this->_event == sdl)
        this->_dl = dlopen("./SDLlib/SDLlib.so", RTLD_LAZY | RTLD_LOCAL);
    else if (this->_event == sfml)
        this->_dl = dlopen("./sfmlLib/sfml.so", RTLD_LAZY | RTLD_LOCAL);
    this->_changeLibrary = false;
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
