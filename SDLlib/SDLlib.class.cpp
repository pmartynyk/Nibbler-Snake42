#include "SDLlib.class.hpp"

extern "C" IDynamicLibrary *createLib(void)
{
	return (new SDLlib());
}

SDLlib::SDLlib(void) : _window(nullptr), _renderer(nullptr) {
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		std::cout << "SDL could not initialize! SDL Error: " <<  SDL_GetError() << std::endl;
		exit(-1);
	}
}
SDLlib::~SDLlib(void) {
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow( _window );
	_window = NULL;
	SDL_Quit();
}

void SDLlib::draw(Snake &snake, int size, Food &food, Score_Time &score_time, bool &endGame)
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);

	this->drawSnake(snake);
	this->drowFood(snake, food, size);
    SDL_RenderPresent(_renderer);

//------
	// static bool tmp = init(size);
	// static bool media = loadMedia();
	

	/* if (endGame)
		this->close();
	else
	{
		this->drowMap(snake, size);
		this->drowFood(snake, food, size);
		this->drawSnake(snake);
		this->drowScore(score_time);
	} */
}

void SDLlib::drowMap(Snake &snake, int size)
{
	_window = SDL_CreateWindow("Nibbler", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size * 16, size * 16, SDL_WINDOW_SHOWN);
    if (_window == nullptr)
    {
		std::cout << "Failed to create a window. SDL Error: " <<  SDL_GetError() << std::endl;
        exit(-1);
    }
    _renderer = SDL_CreateRenderer(_window, -1, 0);
}

void SDLlib::fillMap(Snake &snake, int size)
{
	(void)snake;
	for (int i = 1; i < size - 1; i++)
	{
		for (int j = 1; j < size - 1; j++)
		{
			if (notSnake(snake, i, j))
			{
				/* attron(COLOR_PAIR(3));
				mvprintw(i, j, ".");
				attroff(COLOR_PAIR(3)); */
			}
		}
	}
	// refresh();
}

void SDLlib::drowFood(Snake &snake, Food &food, int size)
{
	SDL_Rect rect;

	if (!food.isAlive())
	{
		rect.w = 16;
		rect.h = 16;

		int tmpX;
		int tmpY;
		tmpX = rand() % (size - 2) + 1;
		tmpY = rand() % (size - 2) + 1;
		food.setAlive(true);
		while (!notSnake(snake, tmpY, tmpX))
		{
			tmpX = rand() % (size - 2) + 1;
			tmpY = rand() % (size - 2) + 1;
		}
		food.setCord(tmpX, tmpY);
		rect.x = food.getX() * 16;
		rect.y = food.getY() * 16;
		SDL_SetRenderDrawColor(_renderer, 0, 0, 200, 255);
    	SDL_RenderFillRect(_renderer, &rect);
	}
	else
	{
		rect.w = 16;
		rect.h = 16;
		rect.x = food.getX() * 16;
		rect.y = food.getY() * 16;
		SDL_SetRenderDrawColor(_renderer, 0, 0, 200, 255);
    	SDL_RenderFillRect(_renderer, &rect);
	}

	//----------------------
/* 	SDL_Rect rect;

    std::pair<int, int> crd = fruit.getCoords();
    rect.w = 16;
    rect.h = 16;
    rect.x = crd.first * 16;
    rect.y = crd.second * 16;
    SDL_SetRenderDrawColor(_renderer, 0, 0, 200, 255);

    SDL_RenderFillRect(_renderer, &rect); */
}

bool SDLlib::notSnake(Snake &snake, int i, int j)
{
	std::list<Unit *>::const_iterator it;
	std::list<Unit *>::const_iterator ite = snake.getUnits().end();
	for (it = snake.getUnits().begin(); it != ite; ++it)
	{
		if ((*it)->getX() == j && (*it)->getY() == i)
		{
			return false;
		}
	}
	return true;
}

void SDLlib::drawSnake(Snake &snake)
{
	SDL_RenderClear(_renderer);
	SDL_Rect rect;

	rect.w = 16;
	rect.h = 16;

	std::list<Unit *>::const_iterator it;
    std::list<Unit *>::const_iterator ite = snake.getUnits().end();
    for (it = snake.getUnits().begin(); it != ite; ++it)
    {
        if ((*it)->isHead())
        {
			rect.x = (*it)->getX() * 16;
			rect.y = (*it)->getY() * 16;
            SDL_SetRenderDrawColor(_renderer, 200, 0, 200, 255);
			SDL_RenderFillRect(_renderer, &rect);
        }
        else
        {
            rect.x = (*it)->getX() * 16;
			rect.y = (*it)->getY() * 16;
            SDL_SetRenderDrawColor(_renderer, 0, 0, 200, 255);
			SDL_RenderFillRect(_renderer, &rect);
        }
    }
}

void SDLlib::drowScore(Score_Time &score_time)
{
	int duration = (std::clock() - score_time.getStart()) / (int)CLOCKS_PER_SEC;
	int minutes;
	int hours;
	int seconds;
	seconds = duration;
	minutes = duration / 60;
	hours = minutes / 60;
	minutes = minutes - hours * 60;
	seconds = seconds - minutes * 60;
	// mvprintw(0, 0, "[SCORE  %d] TIME:  %.2d:%.2d:%.2d", score_time.getScore(), hours, minutes, seconds);
}

Direction SDLlib::checkButton(Direction direction, bool &endGame, Event &event, bool &changeLibrary, bool &move)
{
	SDL_Event e;
	
	//Handle events on queue
	while( SDL_PollEvent( &e ) != 0 )
	{
		//User requests quit
		if( e.type == SDL_QUIT )
		{
			endGame = true;
		}
		//User presses a key
		else if( e.type == SDL_KEYDOWN )
		{
			//Select surfaces based on key press
			switch( e.key.keysym.sym )
			{
				case SDLK_UP:
				{
					direction = up;
					gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
				}
				break;

				case SDLK_DOWN:
				{
					direction = down;
					gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
				}
				break;

				case SDLK_LEFT:
				{
					direction = left;
					gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
				}
				break;

				case SDLK_RIGHT:
				{
					direction = right;
					gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
				}
				break;

				case SDLK_ESCAPE:
				{
					endGame = true;
				}
				break;

				default:
				{
					gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
				}
				break;
			}
		}
	}
	return direction;
}
