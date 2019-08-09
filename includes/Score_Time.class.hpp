#ifndef SCORE_TIME_CLASS_HPP
#define SCORE_TIME_CLASS_HPP

#include <iostream>

class Score_Time
{
private:
    int _score;
    std::clock_t _start;

public:
    Score_Time(void);
    Score_Time(Score_Time const &val);
    Score_Time &operator=(Score_Time const &val);
    ~Score_Time(void);

    int getScore(void);
    std::clock_t getStart(void);
    void addScore(int val);
};

#endif