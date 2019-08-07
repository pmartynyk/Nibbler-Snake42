#include "Ncurses.class.hpp"

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

void Ncurses::draw(Snake &snake, Direction direction, int size)
{
    this->drowMap(snake, size);
    this->drawSnake(snake);
    this->moveSnake(snake, direction);
}

void Ncurses::drowMap(Snake &snake, int size)
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    refresh();
    // resizeterm(size, size);
    wresize(stdscr, size, size);

    box(stdscr, 0, 0);
    fillMap(snake, size);
    wrefresh(stdscr);
    refresh();
}

void Ncurses::fillMap(Snake &snake, int size)
{
    (void)snake;
    for (int i = 1; i < size - 1; i++)
    {
        for (int j = 1; j < size - 1; j++)
        {
            if (notSnake(snake, i, j))
            {
                attron(COLOR_PAIR(3));
                mvprintw(i, j, ".");
                attroff(COLOR_PAIR(3));
            }
        }
    }
    refresh();
}

bool Ncurses::notSnake(Snake &snake, int i, int j)
{
    std::list<Unit *>::const_iterator it;
    std::list<Unit *>::const_iterator ite = snake.getUnits().end();
    for (it = snake.getUnits().begin(); it != ite; ++it)
    {
        if ((*it)->getX() == j && (*it)->getY() == i)
        {
            return false;
        }
    }
    return true;
}

void Ncurses::drawSnake(Snake &snake)
{
    std::list<Unit *>::const_iterator it;
    std::list<Unit *>::const_iterator ite = snake.getUnits().end();
    for (it = snake.getUnits().begin(); it != ite; ++it)
    {
        if ((*it)->isHead())
        {
            attron(COLOR_PAIR(2));
            mvprintw((*it)->getY(), (*it)->getX(), "@");
            attroff(COLOR_PAIR(2));
        }

        else
        {
            attron(COLOR_PAIR(1));
            mvprintw((*it)->getY(), (*it)->getX(), "@");
            attroff(COLOR_PAIR(1));
        }
    }
    refresh();
}

void Ncurses::moveSnake(Snake &snake, Direction direction)
{
    int tmpX;
    int tmpY;
    int tmp1X;
    int tmp1Y;
    std::list<Unit *>::const_iterator it;
    std::list<Unit *>::const_iterator ite = snake.getUnits().end();
    for (it = snake.getUnits().begin(); it != ite; ++it)
    {
        if ((*it)->isHead())
        {
            tmpX = (*it)->getX();
            tmpY = (*it)->getY();
            if (direction == down)
            {
                (*it)->setY((*it)->getY() + 1);
            }
            else if (direction == right)
            {
                (*it)->setX((*it)->getX() + 1);
            }
            else if (direction == left)
            {
                (*it)->setX((*it)->getX() - 1);
            }
            else if (direction == up)
            {
                (*it)->setY((*it)->getY() - 1);
            }
        }
        else
        {
            tmpX = (*it)->getX();
            tmpY = (*it)->getY();
            (*it)->setX(tmp1X);
            (*it)->setY(tmp1Y);
        }
        tmp1X = tmpX;
        tmp1Y = tmpY;
    }
}

Direction Ncurses::checkButton(Direction direction)
{
    int c;

    c = getch();
    if (c == KEY_DOWN)
        return down;
    else if (c == KEY_UP)
        return up;
    else if (c == KEY_LEFT)
        return left;
    else if (c == KEY_RIGHT)
        return right;
    return direction;
}