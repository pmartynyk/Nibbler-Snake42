#ifndef NCURSES_CLASS_HPP
#define NCURSES_CLASS_HPP

#include "../includes/IDynamicLibrary.hpp"
#include "../includes/Snake.class.hpp"
#include <ncurses.h>
#include <iostream>

// class Snake;

class Ncurses : public IDynamicLibrary
{
public:
    Ncurses(void);
    Ncurses(Ncurses const &val);
    Ncurses &operator=(Ncurses const &val);
    ~Ncurses(void);

    void draw(Snake &snake, Direction direction, int size, bool &endGame);

    void drowMap(Snake &snake, int size);
    void fillMap(Snake &snake, int size);
    bool notSnake(Snake &snake, int i, int j);
    void drawSnake(Snake &snake);
    void moveSnake(Snake &snake, Direction direction);
    void checkCollision(Snake &snake, bool &endGame, int size);


    Direction checkButton(Direction direction, bool &endGame);
};

#endif