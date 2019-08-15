#ifndef SFML_CLASS_HPP
#define SFML_CLASS_HPP

#include "../includes/IDynamicLibrary.hpp"
#include "../includes/Snake.class.hpp"
#include "../includes/Food.class.hpp"
#include "../includes/Score_Time.class.hpp"
#include "../includes/Logic.class.hpp"
#include <iostream>
#include <string>
#include "SFML_Lib/SFML-2.5.0-macOS-clang/include/SFML/Graphics.hpp"

class SFML : public IDynamicLibrary
{
private:
	sf::RenderWindow	_window;
	sf::Font			_font;
	bool				_endGame;
	
	sf::Texture _t1;
	sf::Texture _t2;
	sf::Texture _t3;
	sf::Texture _t4;

	sf::Sprite _sprite1;
	sf::Sprite _sprite2;
	sf::Sprite _sprite3;
	sf::Sprite _sprite4;

public:
	SFML(void);
	SFML(SFML const &val);
	~SFML(void);

	void draw(Snake &snake, int size, Food &food, Score_Time &score_time, bool &endGame);

	void drowMap(Snake &snake, int size);
	void drowFood(Snake &snake, Food &food, int size);
	void drowScore(Score_Time &score_time);
	bool notSnake(Snake &snake, int i, int j);
	void drawSnake(Snake &snake);

	Direction checkButton(Direction direction, bool &endGame, Event &event, bool &changeLibrary, bool &move);
	void getStatus(Score_Time &score_time, std::pair <std::string, std::string> &sc);
};

#endif