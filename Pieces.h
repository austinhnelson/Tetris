#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "GhostCube.h"
#include "Cube.h"
#include "Rotation.h"
#include "Setup.h"

class Pieces{
public:
	Pieces(sf::Vector2f position, sf::Vector2f size, std::vector<GhostCube>* ghostCubes, std::vector<Cube>* cubes, Rotation* rotation, sf::RenderWindow* window);
	block getCurrentBlock();
	void run();
private:
	sf::Vector2f position, size;
	std::vector<GhostCube>* ghostCubes;
	std::vector<Cube>* cubes;
	Rotation* rotation;
	sf::RenderWindow* window;
	sf::Image image;
	sf::Texture texture;
	block currentBlock;
	sf::IntRect iBlockIntRect, oBlockIntRect, lBlockIntRect, jBlockIntRect, sBlockIntRect, zBlockIntRect, tBlockIntRect;
	void selector();
	void spawn();
	void spawnPieceIfNoCubesAreActive();
};

