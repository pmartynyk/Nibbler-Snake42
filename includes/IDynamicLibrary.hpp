#ifndef IDYNAMICLIBRARY_HPP
# define IDYNAMICLIBRARY_HPP

class Snake;

enum Direction
{
    right,
    left,
    up,
    down
};

class IDynamicLibrary
{
public:
    virtual void draw(Snake &snake, Direction direction, int size, bool &endGame) = 0;
    virtual Direction checkButton(Direction direction, bool &endGame) = 0;


    // virtual void DrowMap(int size) const = 0;
    // virtual void DrawSnake(Snake &snake)  = 0;
};

#endif