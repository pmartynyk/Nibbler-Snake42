#include "Logic.class.hpp"

Logic::Logic(void)
{
}

Logic::Logic(Logic const &val)
{
    *this = val;
}

Logic &Logic::operator=(Logic const &val)
{
    (void)val;
    return *this;
}

Logic::~Logic(void)
{
}

void Logic::logic(Snake &snake, Food &food, Direction direction, bool &endGame, int size, Score_Time &score_time, IMusic *music)
{
    this->moveSnake(snake, direction);
    this->checkFood(snake, food, score_time, music);
    this->checkCollision(snake, endGame, size, music);
}

void Logic::moveSnake(Snake &snake, Direction direction)
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

void Logic::checkFood(Snake &snake, Food &food, Score_Time &score_time, IMusic *music)
{
    std::list<Unit *>::const_iterator head = snake.getUnits().begin();

    if (food.getX() == (*head)->getX() && food.getY() == (*head)->getY())
    {
        music->playEat();
        food.setAlive(false);
        snake.addUnit();
        score_time.addScore(1);
    }
}


void Logic::checkCollision(Snake &snake, bool &endGame, int size, IMusic *music)
{
    (void)music;
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
                music->playCollision();
                endGame = true;
                return;
            }
        }
    }
}