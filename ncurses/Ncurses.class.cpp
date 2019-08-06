#include "Ncurses.class.hpp"
// #include "../includes/Snake.class.hpp"
// #include "../includes/Unit.class.hpp"

// class Snake;

extern "C" IDynamicLibrary *createLib(void)
{
	return (new Ncurses());
}

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

void Ncurses::DrowMap(int size) const
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
    // resizeterm(size, size);
    wresize(stdscr, size, size);

    box(stdscr, 0, 0);
    fillMap(size);
    wrefresh(stdscr);
    refresh();
}

void Ncurses::fillMap(int size) const
{
    for (int i = 1; i < size - 1; i++)
    {
        for (int j = 1; j < size - 1; j++)
            mvprintw(j, i, ".");
    }
}

void Ncurses::DrawSnake(Snake &snake)
{
    std::list<Unit*>::const_iterator it;
    std::list<Unit*>::const_iterator ite = snake.getUnits().end();
        // std::cout << *it << std::endl;
        // --ite;
        // std::cout << *ite << std::endl;
    //    mvprintw(10, 10, "@");
    int i = 0;
    for (it = snake.getUnits().begin(); it != ite; ++ite)
    {
        // mvprintw((*it)->getX(), (*it)->getY(), "@");
        // mvprintw(5, 5, );
        std::cout << i++ << std::endl;
    }
    // refresh();
}
