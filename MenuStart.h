#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Setup.h"
#define MAX_NUMBER_OF_ITEMS 3
class MenuStart
{
public:
	MenuStart(sf::Vector2f size, sf::RenderWindow* window);
	void draw();
	void moveUp();
	void moveDown();
	int GetPressedItem();
private:
	sf::RenderWindow* window;
	int titleSize, selectedSize, titleYLevelOffset, titleBoxYLevelOffset, itemYLevelOffset, optionBoxYLevelOffset, optionShaderBoxYLevelOffset, selectedItem;
	sf::Vector2f titleBoxSize, optionBoxSize, optionBoxShaderSize;
	sf::Color grey, orange;
	sf::Image startScreenImage;
	sf::Texture startScreenTexture;
	sf::Sprite startScreenSprite;
	sf::Font tetrisFont;
	sf::Text titleText;
	sf::Text text[MAX_NUMBER_OF_ITEMS];
	sf::RectangleShape titleBox, optionBox, optionBoxShader;
	std::vector<sf::RectangleShape> boxes;
};

