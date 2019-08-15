#include "SFML.class.hpp"

extern "C" IDynamicLibrary *createLib(void)
{
	return (new SFML());
}

SFML::SFML(void) : _window(), _circle(16.f)
{
}

SFML::~SFML(void)
{
}

void SFML::draw(Snake &snake, int size, Food &food, Score_Time &score_time, bool &endGame)
{
	if (endGame)
	{
		_window.clear();
		_window.close();
		system("reset");
	}
	else
	{
		this->drowMap(snake, size);
		this->drowFood(snake, food, size);
		this->drawSnake(snake);
		this->drowScore(score_time);
		_window.display();
	}
}

void SFML::drowMap(Snake &snake, int size)
{
	(void)snake;
	(void)size;

	sf::Event event;
	_window.create(sf::VideoMode(size * 20, size * 20), "NIBBLER", sf::Style::Titlebar | sf::Style::Close);

/* 	while (_window.pollEvent(e)) {
		if (e.type == sf::Event::Closed)
			_window.close();
    } */

	while (_window.isOpen())
	{
		while (_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				_window.clear();
				_window.close();
				system("reset");
			}
		}
	}
}

void SFML::fillMap(Snake &snake, int size)
{
	(void)snake;
	for (int i = 1; i < size - 1; i++)
	{
		for (int j = 1; j < size - 1; j++)
		{
			if (notSnake(snake, i, j))
			{
				// attron(COLOR_PAIR(3));
				// mvprintw(i, j, ".");
				// attroff(COLOR_PAIR(3));
			}
		}
	}
	// refresh();
}

void SFML::drowFood(Snake &snake, Food &food, int size)
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
		_circle.setPosition(food.getY(), food.getX());
		_window.draw(_circle);
	}
	else
	{
		_circle.setPosition(food.getY(), food.getX());
		_window.draw(_circle);
	}
}

bool SFML::notSnake(Snake &snake, int i, int j)
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

/* void IGraphicsSFML::DrawSnake(Snake &snake)
{
    std::pair<int, int> head = snake.getHeadCoords();
    std::vector<std::pair<int, int>> tail = snake.getTailCoords();

    sprite3.setPosition(head.first * size, head.second * size);
    window.draw(sprite3);
    for (int i = 0; i < snake.getTailLen(); i++)
    {
        sprite2.setPosition(tail[i].first * size, tail[i].second * size);
        window.draw(sprite2);
    }
} */

void SFML::drawSnake(Snake &snake)
{
	for (auto it : snake.getUnits())
	{
		if (it->isHead())
		{
			_circle.setPosition(it->getY(), it->getX());
			_window.draw(_circle);
		}
		else
		{
			_circle.setPosition(it->getY(), it->getX());
			_window.draw(_circle);
		}
	}
	// refresh();
}

void SFML::drowScore(Score_Time &score_time)
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
	// mvprintw(0, 0, "SCORE: %d TIME:%.2d:%.2d:%.2d", score_time.getScore(), hours, minutes, seconds);
}

Direction SFML::checkButton(Direction direction, bool &endGame, Event &event, bool &changeLibrary, bool &move)
{
	while (_window.pollEvent(e)) {
			if (e.type == sf::Event::Closed)
				_window.close();
		}

	if (move)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && direction != up)
		{
			move = false;
			return down;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && direction != down)
		{
			move = false;
			return up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && direction != right)
		{
			move = false;
			return left;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && direction != left)
		{
			move = false;
			return right;
		}
	}
	if (event == stop && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		event = go;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		endGame = true;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		event = ncurses;
		changeLibrary = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		event = sdl;
		changeLibrary = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		event = sfml;
		changeLibrary = true;
	}
	return direction;
}