#ifndef LOGIC_CLASS_HPP
#define LOGIC_CLASS_HPP

#include "Snake.class.hpp"
#include "IDynamicLibrary.hpp"
#include "IMusic.hpp"
#include "Food.class.hpp"
#include "Score_Time.class.hpp"
#include <ncurses.h>
#include <iostream>

class Logic
{
public:
    Logic(void);
    Logic(Logic const &val);
    Logic &operator=(Logic const &val);
    ~Logic(void);

    void logic(Snake &snake, Food &food, Direction direction, bool &endGame, int size, Score_Time &score_time, IMusic *music);

    void moveSnake(Snake &snake, Direction direction);
    void checkCollision(Snake &snake, bool &endGame, int size, IMusic *music);
    void checkFood(Snake &snake, Food &food, Score_Time &score_time, IMusic *music);

    // Direction checkButton(Direction direction, bool &endGame);
};

#endif