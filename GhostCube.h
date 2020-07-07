#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Rotation.h"

class GhostCube
{
public:
	GhostCube(sf::Vector2f position, sf::IntRect bodyIntRect, sf::Texture* texture, Rotation* rotation, sf::RenderWindow* window);
	sf::Vector2f getPosition();
	sf::Vector2f getSize();
	void setPosition(sf::Vector2f p);
	void increasePosition(sf::Vector2f p);
	void draw();

private:
	sf::Vector2f position, size;
	Rotation* rotation;
	sf::RenderWindow* window;	
	sf::Sprite body;
};

