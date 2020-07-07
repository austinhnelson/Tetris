#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include "Setup.h"
class Map
{
public:
	Map(sf::RenderWindow* window);
	void draw();
private:
	sf::RenderWindow* window;
	sf::Vector2f scale;
	sf::IntRect textBoxCoords;
	sf::Image iconImage, backgroundImage, gridImage, textBoxImage;
	sf::Texture backgroundTexture, gridTexture, textBoxTexture;
	sf::Sprite backgroundSprite, gridSprite, levelSprite, scoreSprite, highScoreSprite;
	std::vector<sf::Sprite> sprites;
};

