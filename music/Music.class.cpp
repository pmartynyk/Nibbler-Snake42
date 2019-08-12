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

void Music::playCollision(void)
{
    system("afplay sound/bgm.mp3 &");
}