#ifndef GAME_CLASS_HPP
#define GAME_CLASS_HPP

#include <iostream>

class Game
{
private:
    int _size;

public:
    Game(int size);
    Game(Game const & val);
    Game &operator=(Game const &val);
    ~Game(void);
    int getSize(void);
};

#endif