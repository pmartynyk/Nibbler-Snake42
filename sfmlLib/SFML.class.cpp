#include "SFML.class.hpp"
#include <sstream>
#include <iomanip>

extern "C" IDynamicLibrary *createLib(void)
{
	return (new SFML());
}

SFML::SFML(void) : _window(), _font(), _endGame(false)
{
	_sprite1.setTexture(_t1);
	_sprite2.setTexture(_t2);
	_sprite3.setTexture(_t3);
	_sprite4.setTexture(_t4);

	_sprite1.setTextureRect(sf::IntRect(0, 0, 28, 28));
	_sprite2.setTextureRect(sf::IntRect(0, 0, 28, 28));
	_sprite3.setTextureRect(sf::IntRect(0, 0, 28, 28));
	_sprite4.setTextureRect(sf::IntRect(0, 0, 28, 28));

	_sprite1.setColor(sf::Color(255, 255, 255));
	_sprite2.setColor(sf::Color(0, 0, 255));
	_sprite3.setColor(sf::Color(0, 255, 0));
	_sprite4.setColor(sf::Color(255, 0, 0));

	if (!_font.loadFromFile("/System/Library/Fonts/Times.ttc"))
	{
		std::cout << "SFML could not initialize!" << std::endl;
		exit(-1);
	}
}

SFML::~SFML(void)
{
}

void SFML::draw(Snake &snake, int size, Food &food, Score_Time &score_time, bool &endGame)
{
	if (endGame)
	{
		this->_endGame = endGame;
		this->drowScore(score_time);

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
	if (!this->_window.isOpen())
	{
		_window.create(sf::VideoMode(size * 30, size * 30), "NIBBLER", sf::Style::Titlebar | sf::Style::Close);
	}
	_window.clear();

	sf::Event event;
	while (_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			_window.close();
		}
	}

	for (int i = 1; i < size - 1; i++)
	{
		for (int j = 1; j < size - 1; j++)
		{
			_sprite1.setPosition(i * 30, j * 30);
			_window.draw(_sprite1);
		}
	}
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
	}
	_sprite4.setPosition(food.getX() * 30, food.getY() * 30);
	_window.draw(_sprite4);
}

bool SFML::notSnake(Snake &snake, int i, int j)
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

void SFML::drawSnake(Snake &snake)
{
	std::list<Unit *>::const_iterator it;
	std::list<Unit *>::const_iterator ite = snake.getUnits().end();
	for (it = snake.getUnits().begin(); it != ite; ++it)
	{
		if ((*it)->isHead())
		{
			_sprite3.setPosition((*it)->getX() * 30, (*it)->getY() * 30);
			_window.draw(_sprite3);
		}
		else
		{
			_sprite2.setPosition((*it)->getX() * 30, (*it)->getY() * 30);
			_window.draw(_sprite2);
		}
	}
}

void SFML::getStatus(Score_Time &score_time, std::pair<std::string, std::string> &sc)
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
	t << "TIME: " << std::setw(2) << std::setfill('0') << hours << ":"
	  << std::setw(2) << std::setfill('0') << minutes << ":"
	  << std::setw(2) << std::setfill('0') << seconds;
	sc.second = t.str().c_str();
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

	std::pair<std::string, std::string> sc;
	getStatus(score_time, sc);

	sf::Text text;
	text.setFont(_font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);

	if (this->_endGame)
	{
		int x = _window.getSize().x;
		int y = _window.getSize().y;
		text.setPosition(x / 2 - 160 , y / 2 - 30);
		text.setCharacterSize(48);
		text.setFillColor(sf::Color::Red);
		text.setStyle(sf::Text::Bold | sf::Text::Underlined);

		text.setString("GAME OVER\n" + sc.first + "\n" + sc.second);
		_window.draw(text);
		_window.display();

		sf::Event event;
		bool esq = true;
		while (_window.pollEvent(event)) 
		{
			while (esq)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
					esq = false;
			}
		}
		_window.close();
	}
	else
	{
		text.setString(sc.first + "\t" + sc.second);
		_window.draw(text);
	}
}

Direction SFML::checkButton(Direction direction, bool &endGame, Event &event, bool &changeLibrary, bool &move)
{
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