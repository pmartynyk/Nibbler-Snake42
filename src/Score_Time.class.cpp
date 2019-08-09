#include "Score_Time.class.hpp"

Score_Time::Score_Time(void) : _score(0)
{
    this->_start = std::clock();
}

Score_Time::Score_Time(Score_Time const &val)
{
    *this = val;
}

Score_Time &Score_Time::operator=(Score_Time const &val)
{
    if (this != &val)
    {
        this->_start = val._start;
        this->_score = val._score;
    }

    return *this;
}

Score_Time::~Score_Time(void)
{
}

int Score_Time::getScore(void)
{
    return this->_score;
}

std::clock_t Score_Time::getStart(void)
{
    return this->_start;
}

void Score_Time::addScore(int val)
{
    this->_score += val;
}