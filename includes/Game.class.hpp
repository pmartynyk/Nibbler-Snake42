#ifndef GAME_CLASS_HPP
#define GAME_CLASS_HPP

#include <iostream>
#include "IDynamicLibrary.hpp"
#include "Ncurses.class.hpp"

class Game
{
private:
    int _size;
    IDynamicLibrary *_library;

public:
    Game(int size);
    Game(Game const & val);
    Game &operator=(Game const &val);
    ~Game(void);
    int getSize(void);

    void play(void);
};

#endif