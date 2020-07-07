#pragma once
#include "SFML/Graphics.hpp"
#include "Score.h"
#include "Setup.h"
class GameOver
{
public:
	GameOver(Score* score, sf::RenderWindow* window);
	void run();
	void draw();
private:
	Score* score;
	sf::RenderWindow* window;
	int defaultCharacterSize;
	sf::RectangleShape gameOverBox, gameOverBoxShader;
	sf::Font font;
	sf::Texture texture;
	sf::Text gameOverText, playAgainText, gameOverScoreText;
	sf::Vector2f gameOverBoxSize, gameOverBoxShaderSize, sizeOffset;
};

