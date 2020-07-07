#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Cube.h"
#include "Manager.h"
#include "MenuStart.h"
#include "Pieces.h"
#include "Rotation.h"
#include "Sounds.h"
class UserInput
{
public:
	UserInput(std::vector<Cube>* cubes, Manager* manager, MenuStart* menu, Pieces* pieces, Rotation* rotation, Sounds* sound, sf::RenderWindow* window);
	void getInput(sf::Event* event);
private:
	std::vector<Cube>* cubes;
	Manager* manager;
	MenuStart* menu;
	Pieces* pieces;
	Rotation* rotation;
	Sounds* sound;
	sf::RenderWindow* window;
	void moveCubeAndRotationLeft();
	void moveCubeAndRotationRight();
	void moveCubeAndRotationDown();
	void rotateCubes();
	void checkPositionIsOpenAndMoveRight();
	void checkPositionIsOpenAndMoveLeft();
	void checkRotateIsCollidedWithLeftWall();
	void checkRotateIsCollidedWithRightWall();
	void dropGhostPieceAndCubesWithSpace();
};

