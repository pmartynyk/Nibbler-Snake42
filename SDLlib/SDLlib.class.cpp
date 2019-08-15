#include "SDLlib.class.hpp"
#include <sstream>
#include <iomanip>

extern "C" IDynamicLibrary *createLib(void)
{
	return (new SDLlib());
}

SDLlib::SDLlib(void)
	: _window(nullptr), _renderer(nullptr), _font(nullptr),
	  _colour({ 255, 255, 255 , 0}), _size(0), _endGame(false) {
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		std::cout << "SDL could not initialize! SDL Error: " <<  SDL_GetError() << std::endl;
		exit(-1);
	}
	if( TTF_Init() < 0 )
	{
		std::cout << "SDL could not initialize! SDL_ttf Error: " <<  SDL_GetError() << std::endl;
		exit(-1);
	}
	this->_font = TTF_OpenFont("/System/Library/Fonts/Times.ttc", 25);
	if( !_font )
	{
		std::cout << "SDL could not initialize! SDL_ttf Error: " <<  TTF_GetError() << std::endl;
		exit(-1);
	}
}

SDLlib::~SDLlib(void) {
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow( _window );
	_window = nullptr;
	SDL_Quit();

	TTF_CloseFont(_font);
	_font = nullptr;
	TTF_Quit();
}

void SDLlib::draw(Snake &snake, int size, Food &food, Score_Time &score_time, bool &endGame)
{
	if (endGame) {
		this->_endGame = endGame;
		this->drowScore(score_time);
	}
	else {
		SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
		SDL_RenderClear(_renderer);

		this->drowMap(snake, size);
		this->_endGame = endGame;
		SDL_Rect field = {16, 16, (size - 2) * 16, (size - 2) * 16};
		SDL_SetRenderDrawColor(_renderer, 30, 30, 30, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(_renderer, &field);

		this->drowScore(score_time);
		this->drawSnake(snake);
		this->drowFood(snake, food, size);
		
		SDL_RenderPresent(_renderer);
	}
}

void SDLlib::drowMap(Snake &, int size)
{
	if (!_window && !_renderer) {
		this->_size = size;
		_window = SDL_CreateWindow("Nibbler", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size * 16, size * 16, SDL_WINDOW_SHOWN);
		if (_window == nullptr)
		{
			std::cout << "Failed to create a window. SDL Error: " <<  SDL_GetError() << std::endl;
			exit(-1);
		}
		_renderer = SDL_CreateRenderer(_window, -1, 0);
		SDL_RenderClear(_renderer);
	}
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
	drawCircle(_renderer, point);
}

bool SDLlib::notSnake(Snake &snake, int i, int j)
{
	for (auto it : snake.getUnits())
	{
		if (it->getX() == j && it->getY() == i)
		{
			return false;
		}
	}
	return true;
}

void SDLlib::drawSnake(Snake &snake)
{
	SDL_Point point;

	for (auto it : snake.getUnits())
	{
		if (it->isHead())
		{
			point.x = it->getX() * 16;
			point.y = it->getY() * 16;
			SDL_SetRenderDrawColor(_renderer, 200, 0, 200, 255);
			drawCircle(_renderer, point);
		}
		else
		{
			point.x = it->getX() * 16;
			point.y = it->getY() * 16;
			SDL_SetRenderDrawColor(_renderer, 0, 0, 200, 255);
			drawCircle(_renderer, point);
		}
	}
}


void SDLlib::getStatus(Score_Time &score_time, std::pair <std::string, std::string> &sc)
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

	std::ostringstream score;
	score << "SCORE: " << std::setw(3) << std::setfill('0') << score_time.getScore();
	sc.first = score.str().c_str();

	std::ostringstream t;
	t << "TIME: "	<< std::setw(2) << std::setfill('0') << hours << ":"
					<< std::setw(2) << std::setfill('0') << minutes << ":"
					<< std::setw(2) << std::setfill('0') << seconds;
	sc.second = t.str().c_str();
}

void SDLlib::drowScore(Score_Time &score_time)
{
	std::pair<std::string, std::string>	sc;
	SDL_Rect							pos{};
	SDL_Surface							*surface;
	SDL_Texture							*texture;

	getStatus(score_time, sc);	

	if (!this->_endGame) {
		std::ostringstream tmp;
		tmp << sc.first << "\t" << sc.second;
		surface = TTF_RenderText_Solid(_font, tmp.str().c_str(), _colour);
		texture = SDL_CreateTextureFromSurface(_renderer, surface);
		SDL_QueryTexture(texture, NULL, NULL, &pos.w, &pos.h);
		SDL_RenderCopy(_renderer, texture, NULL, &pos);
	}
	else {
		int texW = 0;
		int texH = 0;
		surface = TTF_RenderText_Solid(_font, "GAME OVER", _colour);
		texture = SDL_CreateTextureFromSurface(_renderer, surface);
		SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
		pos = { _size / 2 * 16 - (texW / 2), (_size - 1) / 2 * 16, texW, texH };
		SDL_RenderCopy(_renderer, texture, NULL, &pos);

		surface = TTF_RenderText_Solid(_font, sc.first.c_str(), _colour);
		texture = SDL_CreateTextureFromSurface(_renderer, surface);
		SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
		pos.y += 20;
		SDL_RenderCopy(_renderer, texture, NULL, &pos);

		surface = TTF_RenderText_Solid(_font, sc.second.c_str(), _colour);
		texture = SDL_CreateTextureFromSurface(_renderer, surface);
		SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
		pos.y += 20;
		SDL_RenderCopy(_renderer, texture, NULL, &pos);
		SDL_RenderPresent(_renderer);
		
		SDL_Event e;
		SDL_PollEvent( &e );
		while (!((e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) || e.type == SDL_QUIT))
			SDL_PollEvent( &e );
	}
}

Direction SDLlib::checkButton(Direction direction, bool &endGame, Event &event, bool &changeLibrary, bool &move)
{
	SDL_Event e;
	
	while( SDL_PollEvent( &e ) != 0 )
	{
		if( e.type == SDL_QUIT )
		{
			endGame = true;
		}
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

void SDLlib::drawCircle(SDL_Renderer *renderer, SDL_Point &center)
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