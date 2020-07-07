#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Rotation.h"
#include <cmath>
#define PI atan(1) * 4

class Cube
{
public:
	enum class CubeState {
		ACTIVE,
		INACTIVE,
	};
	enum class Quadrant {
		ONE,
		TWO,
		THREE,
		FOUR
	};

	Cube(sf::Vector2f position, sf::IntRect bodyIntRect, sf::Texture* texture, Rotation* rotation, sf::RenderWindow* window);
	sf::Vector2f getPosition();
	sf::Vector2f getSize();
	CubeState getState();
	void setPosition(sf::Vector2f position);
	void setState(CubeState cubeState);
	void increasePosition(sf::Vector2f originPosition);
	void moveActiveUp();
	void moveActiveDown();
	void moveActiveLeft();
	void moveActiveRight();
	Quadrant checkCubeQuadrant(sf::Vector2f position);
	void rotateActive();
	void undoRun();
	void draw();
private:
	sf::Vector2f position, size;
	Rotation* rotation;
	sf::RenderWindow* window;
	sf::Sprite body;
	CubeState cubeState;
	Quadrant quadrant;
};

