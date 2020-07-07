#pragma once
#include "SFML/Graphics.hpp"
#include "Score.h"
#include "Setup.h"

class Text
{
public:
	Text(Score* score, sf::RenderWindow* window);
	void run();
	void draw();
private:
	Score* score;
	sf::RenderWindow* window;
	sf::Font font;
	sf::Text scoreText, levelText;
};

