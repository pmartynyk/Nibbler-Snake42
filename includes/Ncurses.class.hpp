#ifndef NCURSES_CLASS_HPP
#define NCURSES_CLASS_HPP

#include "IDynamicLibrary.hpp"
#include <ncurses.h>
#include <iostream>

class Ncurses : public IDynamicLibrary
{
private:

public:
    Ncurses(void);
    Ncurses(Ncurses const &val);
    Ncurses &operator=(Ncurses const &val);
    ~Ncurses(void);
    void DrowMap(int size);
};

#endif