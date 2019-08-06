#ifndef NCURSES_CLASS_HPP
#define NCURSES_CLASS_HPP

#include "../includes/IDynamicLibrary.hpp"
#include "../includes/Snake.class.hpp"
#include <ncurses.h>
#include <iostream>

// class Snake;

class Ncurses : public IDynamicLibrary
{
public:
    Ncurses(void);
    Ncurses(Ncurses const &val);
    Ncurses &operator=(Ncurses const &val);
    ~Ncurses(void);

    void DrowMap(int size) const;
    void fillMap(int size) const;

    void DrawSnake(Snake &snake);
};

#endif