#ifndef FOOD_CLASS_HPP
#define FOOD_CLASS_HPP

class Food
{
private:
    int _x;
    int _y;
    bool _alive;

public:
    Food(void);
    Food(Food const &val);
    Food &operator=(Food const &val);
    ~Food(void);

    int getX(void);
    int getY(void);

    bool isAlive(void);
    void setCord(int x, int y);
    void setAlive(bool alive);
};

#endif