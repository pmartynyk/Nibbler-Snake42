#include "Ncurses.class.hpp"

extern "C" IDynamicLibrary *createLib(void)
{
    return (new Ncurses());
}

Ncurses::Ncurses(void)
{
}

Ncurses::~Ncurses(void)
{
    erase();
    refresh();
    endwin();
    system("reset");
}

void Ncurses::draw(Snake &snake, int size, Food &food, Score_Time &score_time, bool &endGame)
{
    if (endGame)
    {
        int c;
        WINDOW *end = newwin(7, 20, (size / 2 - 3), (size / 2) - 10);
        int duration = (std::clock() - score_time.getStart()) / (int)CLOCKS_PER_SEC;
        while ((c = getch()) != 27)
        {
            int minutes;
            int hours;
            int seconds;
            seconds = duration;
            minutes = duration / 60;
            hours = minutes / 60;
            minutes = minutes - hours * 60;
            seconds = seconds - minutes * 60;
            box(end, 0, 0);
            mvwprintw(end, 1, 6, "GAMEOVER");
            mvwprintw(end, 3, 2, "SCORE: %d", score_time.getScore());
            mvwprintw(end, 5, 2, "TIME:  %.2d:%.2d:%.2d", hours, minutes, seconds);
            refresh();
            wrefresh(end);
        }
        delwin(end);
        refresh();
        endwin();
    }
    else
    {
        this->drowMap(snake, size);
        this->drowFood(snake, food, size);
        this->drawSnake(snake);
        this->drowScore(score_time);
    }
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

void Ncurses::drowScore(Score_Time &score_time)
{
    int duration = (std::clock() - score_time.getStart()) / (int)CLOCKS_PER_SEC;
    int minutes;
    int hours;
    int seconds;
    seconds = duration;
    minutes = duration / 60;
    hours = minutes / 60;
    minutes = minutes - hours * 60;
    seconds = seconds - minutes * 60;
    mvprintw(0, 0, "SCORE: %d TIME:%.2d:%.2d:%.2d", score_time.getScore(), hours, minutes, seconds);
}

Direction Ncurses::checkButton(Direction direction, bool &endGame, Event &event, bool &changeLibrary, bool &move)
{
    int c;

    c = getch();
    if (move)
    {
        if (c == KEY_DOWN && direction != up)
        {
            move = false;
            return down;
        }
        else if (c == KEY_UP && direction != down)
        {
            move = false;
            return up;
        }
        else if (c == KEY_LEFT && direction != right)
        {
            move = false;
            return left;
        }
        else if (c == KEY_RIGHT && direction != left)
        {
            move = false;
            return right;
        }
    }
    if (event == stop && c == 32)
        event = go;
    if (c == 27)
        endGame = true;
    else if (c == 49)
    {
        event = ncurses;
        changeLibrary = true;
    }
    else if (c == 50)
    {
        event = sdl;
        changeLibrary = true;
    }
    else if (c == 51)
    {
        event = sfml;
        changeLibrary = true;
    }

    return direction;
}
