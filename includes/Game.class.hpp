#ifndef GAME_CLASS_HPP
#define GAME_CLASS_HPP

#include <iostream>
#include <dlfcn.h>
#include "IDynamicLibrary.hpp"
#include "IMusic.hpp"
#include "Snake.class.hpp"
#include "Food.class.hpp"
#include "Score_Time.class.hpp"
#include "Logic.class.hpp"
#include <ncurses.h>

class Game
{
private:
    int             _size;
    IDynamicLibrary *_library;
    IMusic           *_music;
    bool            _endGame; 
    void            *_dl;
    int             _fps;
    Snake           _snake;
    Food            _food;
    Direction       _direction;
    Score_Time      _score_time;

public:
    Game(int size);
    Game(Game const &val);
    Game &operator=(Game const &val);
    ~Game(void);
    int getSize(void);

    void play(void);
    void selectLib(void);
    void setMusic(void);
};

#endif