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

void Logic::logic(Snake &snake, Food &food, Direction direction, bool &endGame, int size, Score_Time &score_time)
{
    this->moveSnake(snake, direction);
    this->checkFood(snake, food, score_time);
    this->checkCollision(snake, endGame, size);
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

void Logic::checkFood(Snake &snake, Food &food, Score_Time &score_time)
{
    std::list<Unit *>::const_iterator head = snake.getUnits().begin();

    if (food.getX() == (*head)->getX() && food.getY() == (*head)->getY())
    {
        food.setAlive(false);
        snake.addUnit();
        score_time.addScore(1);
    }
}

// Direction Logic::checkButton(Direction direction, bool &endGame)
// {
//     int c;

//     c = getch();
//     if (c == KEY_DOWN && direction != up)
//         return down;
//     else if (c == KEY_UP && direction != down)
//         return up;
//     else if (c == KEY_LEFT && direction != right)
//         return left;
//     else if (c == KEY_RIGHT && direction != left)
//         return right;
//     else if (c == 27)
//         endGame = true;
//     return direction;
// }

void Logic::checkCollision(Snake &snake, bool &endGame, int size)
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