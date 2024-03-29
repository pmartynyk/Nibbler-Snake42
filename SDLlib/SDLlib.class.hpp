#ifndef SDLLIB_CLASS_HPP
# define SDLLIB_CLASS_HPP

#include "../includes/IDynamicLibrary.hpp"
#include "../includes/Snake.class.hpp"
#include "../includes/Food.class.hpp"
#include "../includes/Score_Time.class.hpp"
#include "../includes/Logic.class.hpp"

#include "./SDL/SDL2.framework/Versions/A/Headers/SDL.h"
#include "./SDL/SDL2_ttf.framework/Versions/A/Headers/SDL_ttf.h"

class SDLlib : public IDynamicLibrary
{
private:
    SDL_Window      *_window;
    SDL_Renderer    *_renderer;
    TTF_Font        *_font;
    SDL_Color       _colour;
    int             _size;
    bool            _endGame;

public:
    SDLlib(void);
    SDLlib(SDLlib const &val) = delete;
    SDLlib &operator=(SDLlib const &val) = delete;
    ~SDLlib(void);

    void draw(Snake &snake, int size, Food &food, Score_Time &score_time, bool &endGame);

    void drawCircle(SDL_Renderer *renderer, SDL_Point &center);
    void drowMap(Snake &snake, int size);
    void drowFood(Snake &snake, Food &food, int size);
    void drowScore(Score_Time &score_time);
    bool notSnake(Snake &snake, int i, int j);
    void drawSnake(Snake &snake);
    Direction checkButton(Direction direction, bool &endGame, Event &event, bool &changeLibrary, bool &move);
    void getStatus(Score_Time &score_time, std::pair <std::string, std::string> &sc);
};

#endif //SDLLIB_CLASS_HPP