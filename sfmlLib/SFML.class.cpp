#include "SFML.class.hpp"

extern "C" IDynamicLibrary *createLib(void)
{
    return (new SFML());
}

SFML::SFML(void)
{
}

SFML::~SFML(void)
{
}

void SFML::draw(Snake &snake, int size, Food &food, Score_Time &score_time, bool &endGame)
{
    if (endGame)
    {
        window.clear();
        window.close();
        system("reset");
    }
    else
    {
        this->drowMap(snake, size);
        this->drowFood(snake, food, size);
        this->drawSnake(snake);
        this->drowScore(score_time);
        window.display();
    }
}

void SFML::drowMap(Snake &snake, int size)
{
    (void)snake;
    (void)size;

    sf::Event event;
    window.create(sf::VideoMode(size * 20, size * 20), "NIBBLER");
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.clear();
                window.close();
                system("reset");
            }
        }
    }
}

void SFML::fillMap(Snake &snake, int size)
{
    (void)snake;
    for (int i = 1; i < size - 1; i++)
    {
        for (int j = 1; j < size - 1; j++)
        {
            if (notSnake(snake, i, j))
            {
                // attron(COLOR_PAIR(3));
                // mvprintw(i, j, ".");
                // attroff(COLOR_PAIR(3));
            }
        }
    }
    // refresh();
}

void SFML::drowFood(Snake &snake, Food &food, int size)
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
        // attron(COLOR_PAIR(4));
        // mvprintw(food.getY(), food.getX(), "o");
        // attroff(COLOR_PAIR(4));
    }
    else
    {
        // attron(COLOR_PAIR(4));
        // mvprintw(food.getY(), food.getX(), "o");
        // attroff(COLOR_PAIR(4));
    }
}

bool SFML::notSnake(Snake &snake, int i, int j)
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

void SFML::drawSnake(Snake &snake)
{
    std::list<Unit *>::const_iterator it;
    std::list<Unit *>::const_iterator ite = snake.getUnits().end();
    for (it = snake.getUnits().begin(); it != ite; ++it)
    {
        if ((*it)->isHead())
        {
            // attron(COLOR_PAIR(2));
            // mvprintw((*it)->getY(), (*it)->getX(), "@");
            // attroff(COLOR_PAIR(2));
        }
        else
        {
            // attron(COLOR_PAIR(1));
            // mvprintw((*it)->getY(), (*it)->getX(), "@");
            // attroff(COLOR_PAIR(1));
        }
    }
    // refresh();
}

void SFML::drowScore(Score_Time &score_time)
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
    // mvprintw(0, 0, "SCORE: %d TIME:%.2d:%.2d:%.2d", score_time.getScore(), hours, minutes, seconds);
}

Direction SFML::checkButton(Direction direction, bool &endGame, Event &event, bool &changeLibrary, bool &move)
{
    if (move)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && direction != up)
        {
            move = false;
            return down;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && direction != down)
        {
            move = false;
            return up;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && direction != right)
        {
            move = false;
            return left;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && direction != left)
        {
            move = false;
            return right;
        }
    }
    if (event == stop && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        event = go;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        endGame = true;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
    {
        event = ncurses;
        changeLibrary = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
    {
        event = sdl;
        changeLibrary = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
    {
        event = sfml;
        changeLibrary = true;
    }
    return direction;
}