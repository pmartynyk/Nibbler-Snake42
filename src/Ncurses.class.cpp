#include "../includes/Ncurses.class.hpp"

Ncurses::Ncurses(void)
{
}

Ncurses::Ncurses(Ncurses const &val)
{
    *this = val;
}

Ncurses &Ncurses::operator=(Ncurses const &val)
{
    if (this != &val)
    {
    }
    return *this;
}

Ncurses::~Ncurses(void)
{
}

void Ncurses::DrowMap(int size)
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
    resizeterm(size, size);
    //
    box(stdscr, 0, 0);
    refresh();
}