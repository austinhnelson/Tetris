#pragma once
#include "SFML/Graphics.hpp"
#include "Setup.h"

class Rotation
{
public:
	Rotation(sf::Vector2f moveSize, sf::RenderWindow* window);
	void setPosition(sf::Vector2f p);
	sf::Vector2f getPosition();
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void run();
	void draw();
private:
	float radius;
	sf::Vector2f moveSize;
	sf::RenderWindow* window;
	sf::CircleShape rotationPoint;
	sf::Vector2f rotationPos;
	block currentBlock;
};

