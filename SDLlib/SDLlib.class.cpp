#include "SDLlib.class.hpp"

extern "C" IDynamicLibrary *createLib(void)
{
	return (new SDLlib());
}

void draw_circle(SDL_Renderer * renderer, SDL_Point center)
{
	int radius = 8;
	for (int w = 0; w < radius * 2; w++)
	{
		for (int h = 0; h < radius * 2; h++)
		{
			int dx = radius - w;
			int dy = radius - h;
			if ((dx*dx + dy*dy) <= (radius * radius))
				SDL_RenderDrawPoint(renderer, center.x + dx + 8, center.y + dy + 8);
		}
	}
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
	if (endGame) {
		(void)score_time;
	}
	else {
		SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
		SDL_RenderClear(_renderer);

		static bool i = true;

		if (i) {
			this->drowMap(snake, size);
			i = false;
		}
		
		this->drawSnake(snake);
		this->drowFood(snake, food, size);
		SDL_RenderPresent(_renderer);
	}
}

void SDLlib::drowMap(Snake &, int size)
{
	_window = SDL_CreateWindow("Nibbler", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size * 16, size * 16, SDL_WINDOW_SHOWN);
	if (_window == nullptr)
	{
		std::cout << "Failed to create a window. SDL Error: " <<  SDL_GetError() << std::endl;
		exit(-1);
	}
	_renderer = SDL_CreateRenderer(_window, -1, 0);
}

void SDLlib::drowFood(Snake &snake, Food &food, int size)
{
	SDL_Point point;

	if (!food.isAlive())
	{
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
	}
	point.x = food.getX() * 16;
	point.y = food.getY() * 16;
	SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 0);
	draw_circle(_renderer, point);
}

bool SDLlib::notSnake(Snake &snake, int i, int j)
{
	for (auto it : snake.getUnits())
	{
		if ((*it).getX() == j && (*it).getY() == i)
		{
			return false;
		}
	}
	return true;
}

void SDLlib::drawSnake(Snake &snake)
{
	SDL_RenderClear(_renderer);
	SDL_Point point;

	for (auto it : snake.getUnits())
	{
		if ((*it).isHead())
		{
			point.x = (*it).getX() * 16;
			point.y = (*it).getY() * 16;
			SDL_SetRenderDrawColor(_renderer, 200, 0, 200, 255);
			draw_circle(_renderer, point);
		}
		else
		{
			point.x = (*it).getX() * 16;
			point.y = (*it).getY() * 16;
			SDL_SetRenderDrawColor(_renderer, 0, 0, 200, 255);
			draw_circle(_renderer, point);
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
			int c = e.key.keysym.sym;
			if (move)
			{
				if (c == SDLK_DOWN && direction != up)
				{
					move = false;
					return down;
				}
				else if (c == SDLK_UP && direction != down)
				{
					move = false;
					return up;
				}
				else if (c == SDLK_LEFT && direction != right)
				{
					move = false;
					return left;
				}
				else if (c == SDLK_RIGHT && direction != left)
				{
					move = false;
					return right;
				}
			}
			if (event == stop && c == 32)
				event = go;
			if (c == SDLK_ESCAPE)
			{
				endGame = true;
			}
			else if (c == SDLK_1)
			{
				event = ncurses;
				changeLibrary = true;
			}
			else if (c == SDLK_2)
			{
				event = sdl;
				changeLibrary = true;
			}
			else if (c == SDLK_3)
			{
				event = sfml;
				changeLibrary = true;
			} 
		}
	}
	return direction;
}
