#ifndef SDLLIB_CLASS_HPP
# define SDLLIB_CLASS_HPP

#include "../includes/IDynamicLibrary.hpp"
#include "../includes/Snake.class.hpp"
#include "../includes/Food.class.hpp"
#include "../includes/Score_Time.class.hpp"
#include "../includes/Logic.class.hpp"

// #include <SDL2/SDL.h>
#include "./SDL/SDL2.framework/Versions/A/Headers/SDL.h"

//Key press surfaces constants
enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
	
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The images that correspond to a keypress
SDL_Surface* gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];

//Current displayed image
SDL_Surface* gCurrentSurface = NULL;

class SDLlib : public IDynamicLibrary
{
public:
    SDLlib(void);
    SDLlib(SDLlib const &val);
    SDLlib &operator=(SDLlib const &val);
    ~SDLlib(void);

    void draw(Snake &snake, int size, Food &food, Score_Time &score_time, bool &endGame);

    void drowMap(Snake &snake, int size);
    void drowFood(Snake &snake, Food &food, int size);
    void drowScore(Score_Time &score_time);
    void fillMap(Snake &snake, int size);
    bool notSnake(Snake &snake, int i, int j);
    void drawSnake(Snake &snake);
    // void moveSnake(Snake &snake, Direction direction);
    // void checkCollision(Snake &snake, bool &endGame, int size);
    // void checkFood(Snake &snake, Food &food, Score_Time &score_time);

    Direction checkButton(Direction direction, bool &endGame, Direction &library);

    void close();
    bool init(int size);
};

#endif //SDLLIB_CLASS_HPP