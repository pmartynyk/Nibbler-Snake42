#ifndef IDYNAMICLIBRARY_HPP
# define IDYNAMICLIBRARY_HPP

class Snake;

class IDynamicLibrary
{
public:
    virtual void DrowMap(int size) const = 0;
    virtual void DrawSnake(Snake &snake)  = 0;
};

#endif