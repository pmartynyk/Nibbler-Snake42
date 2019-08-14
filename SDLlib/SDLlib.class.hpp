#ifndef SDLLIB_CLASS_HPP
# define SDLLIB_CLASS_HPP

#include "../includes/IDynamicLibrary.hpp"
#include "../includes/Snake.class.hpp"
#include "../includes/Food.class.hpp"
#include "../includes/Score_Time.class.hpp"
#include "../includes/Logic.class.hpp"

// #include <SDL2/SDL.h>
#include "./SDL/SDL2.framework/Versions/A/Headers/SDL.h"

class SDLlib : public IDynamicLibrary
{
private:
    SDL_Window      *_window;
    SDL_Renderer    *_renderer;
public:
    SDLlib(void);
    SDLlib(SDLlib const &val);
    SDLlib &operator=(SDLlib const &val);
    ~SDLlib(void);

    void draw(Snake &snake, int size, Food &food, Score_Time &score_time, bool &endGame);

    void drowMap(Snake &snake, int size);
    void drowFood(Snake &snake, Food &food, int size);
    void drowScore(Score_Time &score_time);
    bool notSnake(Snake &snake, int i, int j);
    void drawSnake(Snake &snake);

    Direction checkButton(Direction direction, bool &endGame, Event &event, bool &changeLibrary, bool &move);
};

#endif //SDLLIB_CLASS_HPP