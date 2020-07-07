#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Cube.h"
#include "GameOver.h"
#include "GhostCube.h"
#include "HighScore.h"
#include "Pieces.h"
#include "Setup.h"
#include "Score.h"
#include "Map.h"
#include "MenuStart.h"
#include "Sounds.h"
#include "Text.h"

class Manager
{
public:
	enum class GameState {
		START,
		RUNNING,
		OVER
	};
	Manager(std::vector<Cube>* cubes, GameOver* gameOver, std::vector<GhostCube>* ghostCubes, HighScore* highScore, Map* map, MenuStart* menu, Pieces* pieces, Rotation* rotation, Score* score, Sounds* sound, Text* text, sf::RenderWindow* window);
	GameState getState();
	void setState(GameState s);
	bool anyActiveCubesOnGround();
	bool anyCubesCollided();
	bool areCubesCollidedWithWall();
	bool areCubesCollidedWithLeftWall();
	bool areCubesCollidedWithRightWall();
	void eraseAllGhosts();
	void dropGhostPiece();
	void resetAndRestart();
	void run();
	void draw();
private:
	std::vector<Cube>* cubes;
	GameOver* gameOver;
	std::vector<GhostCube>* ghostCubes;
	HighScore* highScore;
	Map* map;
	MenuStart* menu;
	Pieces* pieces;
	Rotation* rotation;
	Score* score;
	Sounds* sound;
	Text* text;
	sf::RenderWindow* window;
	GameState gameState;
	std::vector<int> indexPlacementForCompletedRows;
	sf::Clock clock;
	sf::Time previousTime, currentTime, elapsedTime;
	float speedThreshold, height, deleteCounter, ySaved, defaultThreshold, incrementThreshold, maxNumberOfPieces;
	bool anyGhostOnGround();
	bool anyGhostCollided();
	bool isRowComplete();
	void undoAllActiveRuns();
	void checkForGameOverAndSet();
	void setAllCubesState(Cube::CubeState s);
	void increaseSpeedThreshold(int level);
	void deleteRowsThatAreFull();
	void shiftAllDownWhenDeleted();
};

