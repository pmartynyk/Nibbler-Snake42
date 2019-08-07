#ifndef GAME_CLASS_HPP
#define GAME_CLASS_HPP

#include <iostream>
#include <dlfcn.h>
#include "IDynamicLibrary.hpp"
#include "Snake.class.hpp"

// enum Direction
// {
//     right,
//     left,
//     up,
//     down
// };

class Game
{
private:
    int _size;
    IDynamicLibrary *_library;
    bool _endGame;
    void *_dl;
    int _fps;
    Snake _snake;
    Direction _direction;

public:
    Game(int size);
    Game(Game const &val);
    Game &operator=(Game const &val);
    ~Game(void);
    int getSize(void);

    void play(void);
    void selectLib(void);

};

#endif