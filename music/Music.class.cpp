#include "Music.class.hpp"

extern "C" IMusic *create(void)
{
    return (new Music());
}

Music::Music(void)
{
}

Music::Music(Music const &val)
{
    *this = val;
}

Music &Music::operator=(Music const &val)
{
    (void)val;
    if (this != &val)
    {
    }
    return *this;
}

Music::~Music(void)
{
}

void Music::playEat(void)
{
    system("say oum&");
}

void Music::playCollision(void)
{
    system("say ouou&");
}