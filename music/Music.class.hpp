#ifndef MUSIC_CLASS_HPP
#define MUSIC_CLASS_HPP

#include "../includes/IMusic.hpp"
#include <iostream>

class Music : public IMusic
{
public:
  Music(void);
  Music(Music const &val);
  Music &operator=(Music const &val);
  ~Music(void);

  void playCollision(void);
};

#endif