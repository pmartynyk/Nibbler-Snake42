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

void Ncurses::draw(Snake &snake, Direction direction, int size, bool &endGame, Food &food)
{
    this->moveSnake(snake, direction);
    this->checkFood(snake, food);
    this->drowMap(snake, size);
    this->drowFood(snake, food, size);
    this->checkCollision(snake, endGame, size);

    if (endGame)
        endwin();
    else
        this->drawSnake(snake);
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
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    refresh();
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

void Ncurses::drowFood(Snake &snake, Food &food, int size)
{
    if (!food.isAlive())
    {
        int tmpX;
        int tmpY;
        tmpX = rand() % (size - 2) + 1;
        tmpY = rand() % (size - 2) + 1;

        food.setAlive(true);

        while (!notSnake(snake, tmpY, tmpX))
        {
            tmpX = rand() % (size - 2) + 1;
            tmpY = rand() % (size - 2) + 1;
        }
        // tmpX = ((tmpX <= 1 || tmpX >= size - 1) ? size / 4 : tmpX);
        // tmpY = ((tmpY <= 1 || tmpY >= size - 1) ? size / 2 : tmpY);
        food.setCord(tmpX, tmpY);
        attron(COLOR_PAIR(4));
        mvprintw(food.getY(), food.getX(), "o");
        attroff(COLOR_PAIR(4));
    }
    else
    {
        attron(COLOR_PAIR(4));
        mvprintw(food.getY(), food.getX(), "o");
        attroff(COLOR_PAIR(4));
    }
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
            (*it)->setPrevX(tmpX);
            (*it)->setPrevY(tmpY);
            (*it)->setX(tmp1X);
            (*it)->setY(tmp1Y);
        }
        tmp1X = tmpX;
        tmp1Y = tmpY;
    }
}

void Ncurses::checkFood(Snake &snake, Food &food)
{
    std::list<Unit *>::const_iterator head = snake.getUnits().begin();

    if (food.getX() == (*head)->getX() && food.getY() == (*head)->getY())
    {
        food.setAlive(false);
        snake.addUnit();
    }
}

Direction Ncurses::checkButton(Direction direction, bool &endGame)
{
    int c;

    c = getch();
    if (c == KEY_DOWN && direction != up)
        return down;
    else if (c == KEY_UP && direction != down)
        return up;
    else if (c == KEY_LEFT && direction != right)
        return left;
    else if (c == KEY_RIGHT && direction != left)
        return right;
    else if (c == 27)
        endGame = true;
    return direction;
}

void Ncurses::checkCollision(Snake &snake, bool &endGame, int size)
{
    std::list<Unit *>::const_iterator head = snake.getUnits().begin();
    if ((*head)->getX() < 1 || (*head)->getY() < 1 || (*head)->getX() >= size - 1 || (*head)->getY() >= size - 1)
        endGame = true;
    std::list<Unit *>::const_iterator it;
    std::list<Unit *>::const_iterator ite = snake.getUnits().end();
    for (it = snake.getUnits().begin(); it != ite; ++it)
    {
        if (!(*it)->isHead())
        {
            if ((*head)->getX() == (*it)->getX() && (*head)->getY() == (*it)->getY())
            {
                endGame = true;
                return;
            }
        }
    }
}