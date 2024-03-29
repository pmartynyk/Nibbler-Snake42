#ifndef IDYNAMICLIBRARY_HPP
#define IDYNAMICLIBRARY_HPP

class Snake;
class Food;
class Score_Time;

enum Direction
{
    right,
    left,
    up,
    down

};

enum Event
{
    ncurses,
    sdl,
    sfml,
    stop,
    go
};

class IDynamicLibrary
{
  public:
    virtual ~IDynamicLibrary(void){};
    virtual void draw(Snake &snake, int size, Food &food, Score_Time &score_time, bool &endGame) = 0;
    virtual Direction checkButton(Direction direction, bool &endGame, Event &event, bool &changeLibrary, bool &move) = 0;

    virtual void drowMap(Snake &snake, int size) = 0;
    virtual void drowFood(Snake &snake, Food &food, int size) = 0;
    virtual void drowScore(Score_Time &score_time) = 0;
    virtual void drawSnake(Snake &snake) = 0;
};

#endif