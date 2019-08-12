#include "SDLlib.class.hpp"

extern "C" IDynamicLibrary *createLib(void)
{
	return (new SDLlib());
}

SDLlib::SDLlib(void) {}
SDLlib::~SDLlib(void) {}

void SDLlib::draw(Snake &snake, int size, Food &food, Score_Time &score_time, bool &endGame)
{
	static bool tmp = init(size);
	// static bool media = loadMedia();
	

	if (endGame)
		this->close();
	else
	{
		this->drowMap(snake, size);
		this->drowFood(snake, food, size);
		this->drawSnake(snake);
		this->drowScore(score_time);

		//Apply the current image
		SDL_BlitSurface( gCurrentSurface, NULL, gScreenSurface, NULL );
	
		//Update the surface
		SDL_UpdateWindowSurface( gWindow );
	}
}

bool SDLlib::init(int size)
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, size, size, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface( gWindow );
		}
	}

	return success;
}

SDL_Surface* loadSurface( std::string path )
{
	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
	}

	return loadedSurface;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load default surface
	gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] = loadSurface( "04_key_presses/press.bmp" );
	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load up surface
	gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] = loadSurface( "04_key_presses/up.bmp" );
	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] == NULL )
	{
		printf( "Failed to load up image!\n" );
		success = false;
	}

	//Load down surface
	gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] = loadSurface( "04_key_presses/down.bmp" );
	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] == NULL )
	{
		printf( "Failed to load down image!\n" );
		success = false;
	}

	//Load left surface
	gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] = loadSurface( "04_key_presses/left.bmp" );
	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] == NULL )
	{
		printf( "Failed to load left image!\n" );
		success = false;
	}

	//Load right surface
	gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] = loadSurface( "04_key_presses/right.bmp" );
	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] == NULL )
	{
		printf( "Failed to load right image!\n" );
		success = false;
	}

	return success;
}

void SDLlib::close()
{
	//Deallocate surfaces
	for( int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i )
	{
		SDL_FreeSurface( gKeyPressSurfaces[ i ] );
		gKeyPressSurfaces[ i ] = NULL;
	}

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

void SDLlib::drowMap(Snake &snake, int size)
{
	
/* 	if( !init(size * 20) )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//Set default current surface
			gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					//User presses a key
					else if( e.type == SDL_KEYDOWN )
					{
						//Select surfaces based on key press
						switch( e.key.keysym.sym )
						{
							case SDLK_UP:
							gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
							break;

							case SDLK_DOWN:
							gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
							break;

							case SDLK_LEFT:
							gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
							break;

							case SDLK_RIGHT:
							gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
							break;

			  				case SDLK_ESCAPE:
							quit = true;
							break;

							default:
							gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
							break;
						}
					}
				}

				//Apply the current image
				SDL_BlitSurface( gCurrentSurface, NULL, gScreenSurface, NULL );
			
				//Update the surface
				SDL_UpdateWindowSurface( gWindow );
			}
		}
	} */

	//Free resources and close SDL
	// close();

	/* initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	curs_set(0);
	start_color();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	refresh();
	wresize(stdscr, size, size);

	// box(stdscr, 0, 1);
	fillMap(snake, size);
	wrefresh(stdscr);
	refresh(); */
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
		/* attron(COLOR_PAIR(4));
		mvprintw(food.getY(), food.getX(), "o");
		attroff(COLOR_PAIR(4)); */
	}
	else
	{
	   /*  attron(COLOR_PAIR(4));
		mvprintw(food.getY(), food.getX(), "o");
		attroff(COLOR_PAIR(4)); */
	}
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
	std::list<Unit *>::const_iterator it;
	std::list<Unit *>::const_iterator ite = snake.getUnits().end();
	for (it = snake.getUnits().begin(); it != ite; ++it)
	{
		if ((*it)->isHead())
		{
			/* attron(COLOR_PAIR(2));
			mvprintw((*it)->getY(), (*it)->getX(), "@");
			attroff(COLOR_PAIR(2)); */
		}
		else
		{
			/* attron(COLOR_PAIR(1));
			mvprintw((*it)->getY(), (*it)->getX(), "@");
			attroff(COLOR_PAIR(1)); */
		}
	}
	// refresh();
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

Direction SDLlib::checkButton(Direction direction, bool &endGame)
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
