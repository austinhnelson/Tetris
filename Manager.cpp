#include "Manager.h"

Manager::Manager(std::vector<Cube>* cubes, GameOver* gameOver, std::vector<GhostCube>* ghostCubes, HighScore* highScore, Map* map, MenuStart* menu, Pieces* pieces, Rotation* rotation, Score* score, Sounds* sound, Text* text, sf::RenderWindow* window){
	this->cubes = cubes;
	this->gameOver = gameOver;
	this->ghostCubes = ghostCubes;
	this->highScore = highScore;
	this->map = map;
	this->menu = menu;
	this->pieces = pieces;
	this->rotation = rotation;
	this->score = score; 
	this->sound = sound;
	this->text = text;
	this->window = window;
	defaultThreshold = .25;
	incrementThreshold = .02;
	maxNumberOfPieces = 201;
	speedThreshold = defaultThreshold;
	gameState = GameState::START;
	deleteCounter = height = 0;
	previousTime = clock.getElapsedTime();
}

//public methods
Manager::GameState Manager::getState() {
	return gameState;
}

void Manager::setState(GameState s) {
	gameState = s;
}

bool Manager::anyActiveCubesOnGround() {
	for (int i = 0; i < cubes->size(); i++) {
		float y = cubes->at(i).getPosition().y;
		if (y >= PLAY_ARENA_Y + INITIAL_PLAYER_Y) { 
			return true;
		}
	}
	return false;
}

bool Manager::anyCubesCollided() {
	for (int i = 0; i < cubes->size(); i++) {
		for (int j = i + 1; j < cubes->size(); j++) {
			if (cubes->at(i).getPosition().x >= cubes->at(j).getPosition().x + cubes->at(j).getSize().x || cubes->at(i).getPosition().x + cubes->at(i).getSize().x <= cubes->at(j).getPosition().x) {
				continue;
			}
			else if (cubes->at(i).getPosition().y >= cubes->at(j).getPosition().y + cubes->at(j).getSize().y || cubes->at(i).getPosition().y + cubes->at(i).getSize().y <= cubes->at(j).getPosition().y) {
				continue;
			}
			else {
				return true;
			}
		}
	}
	return false;
}

bool Manager::areCubesCollidedWithWall() {
	for (int i = 0; i < cubes->size(); i++) {
		if (cubes->at(i).getPosition().x < INITIAL_PLAYER_X || cubes->at(i).getPosition().x + cubes->at(i).getSize().x > PLAY_ARENA_X + INITIAL_PLAYER_X) {
			return true;
		}
	}
	return false;
}

bool Manager::areCubesCollidedWithLeftWall() {
	for (int i = 0; i < cubes->size(); i++) {
		if (cubes->at(i).getState() == Cube::CubeState::ACTIVE) {
			if (cubes->at(i).getPosition().x < INITIAL_PLAYER_X) {
				return true;
			}
		}
	}
	return false;
}

bool Manager::areCubesCollidedWithRightWall() {
	for (int i = 0; i < cubes->size(); i++) {
		if (cubes->at(i).getPosition().x + cubes->at(i).getSize().x > PLAY_ARENA_X + INITIAL_PLAYER_X) {
			return true;
		}
	}
	return false;
}

void Manager::eraseAllGhosts() {
	ghostCubes->clear();
}

void Manager::dropGhostPiece() {
	int cubeActiveCounter = 0;
	for (int cubeCount = 0; cubeCount < cubes->size(); cubeCount++) {
		if (cubes->at(cubeCount).getState() == Cube::CubeState::ACTIVE) {
			if (cubeActiveCounter == 0) {
				ySaved = cubes->at(cubeCount).getPosition().y;
			}
			ghostCubes->at(cubeActiveCounter).setPosition(cubes->at(cubeCount).getPosition());
			cubeActiveCounter++;
			if (cubeActiveCounter == 4) { // 4 is the number of cubes in each piece
				break;
			}
		}
	}

	int bottomYLevel = PLAY_ARENA_Y + INITIAL_PLAYER_Y - CUBE_SIZE_Y; //gets bottom y level

	for (int i = ySaved; i < bottomYLevel; i += CUBE_SIZE_Y) { //looping through all y levels present in grid 
		for (int count = 0; count < ghostCubes->size(); count++) {
			ghostCubes->at(count).increasePosition(sf::Vector2f(0, ghostCubes->at(count).getSize().y));
		}
		if (anyGhostCollided()) { //if any ghost collided it will raise all of the cubes up
			for (int count = 0; count < ghostCubes->size(); count++) {
				ghostCubes->at(count).increasePosition(sf::Vector2f(0, -ghostCubes->at(count).getSize().y));
			}
		}
	}

	while (anyGhostOnGround()) { //if any ghost on the ground it will move all of them up so they dont appear on ground
		for (int count = 0; count < ghostCubes->size(); count++) {
			ghostCubes->at(count).increasePosition(sf::Vector2f(0, -ghostCubes->at(count).getSize().y));
		}
	}
}

void Manager::resetAndRestart() {
	for (int i = cubes->size() - 1; i >= 0; i--) {
		cubes->erase(cubes->begin() + i);
	}
	ghostCubes->clear();
	score->resets();
	highScore->resetHighScoreState();
	speedThreshold = defaultThreshold;
	gameState = GameState::START;
}

void Manager::run() {
	sound->play();
	if (gameState == GameState::RUNNING) {
		checkForGameOverAndSet();
		currentTime = clock.getElapsedTime();
		elapsedTime = currentTime - previousTime;
		//only do run after a set amount of time is elasped
		text->run();
		highScore->run();
		pieces->run();
		rotation->run();
		dropGhostPiece();
		if (anyActiveCubesOnGround() || anyCubesCollided()) {
			undoAllActiveRuns();
			setAllCubesState(Cube::CubeState::INACTIVE);
		}
		if (elapsedTime.asSeconds() >= speedThreshold) {
			for (int i = 0; i < cubes->size(); i++) {
				cubes->at(i).moveActiveDown();
			}
			rotation->moveDown();
			previousTime = clock.getElapsedTime();
			currentTime = clock.getElapsedTime();
		}
		if (isRowComplete()) {
			for (int i = indexPlacementForCompletedRows.size(); i < maxNumberOfPieces; i++) { //
				indexPlacementForCompletedRows.push_back(maxNumberOfPieces); //place holder so vector is bigger than cubes
			}
			deleteRowsThatAreFull();
			shiftAllDownWhenDeleted();
			score->increaseNumberOfLinesCleared(deleteCounter);
			increaseSpeedThreshold(score->getLevel());
			deleteCounter = 0;
		}
	}
	else if (gameState == GameState::OVER) {
		highScore->saveScore(score->getScore());
		gameOver->run();
	}
}

void Manager::draw() {
	if (gameState == GameState::RUNNING || gameState == GameState::OVER) {
		map->draw();
		for (int i = 0; i < cubes->size(); i++) {
			cubes->at(i).draw();
		}
		for (int i = 0; i < ghostCubes->size(); i++) {
			ghostCubes->at(i).draw();
		}
		text->draw();
		highScore->draw();
		if (gameState == GameState::OVER) {
			gameOver->draw();
		}
	}
	else if (gameState == GameState::START) {
		menu->draw();
	}
}

//private methods
bool Manager::anyGhostOnGround() {
	for (int i = 0; i < ghostCubes->size(); i++) {
		if (ghostCubes->at(i).getPosition().y >= PLAY_ARENA_Y + INITIAL_PLAYER_Y) {
			return true;
		}
	}
	return false;
}

bool Manager::anyGhostCollided() {
	for (int ghostCount = 0; ghostCount < ghostCubes->size(); ghostCount++) {
		for (int cubeCount = 0; cubeCount < cubes->size(); cubeCount++) {
			if (cubes->at(cubeCount).getState() == Cube::CubeState::INACTIVE) {
				if (ghostCubes->at(ghostCount).getPosition() == cubes->at(cubeCount).getPosition()) {
					return true;
				}
			}
		}
	}
	return false;
}

bool Manager::isRowComplete() {
	int counter = height = 0;
	for (int yLevel = INITIAL_PLAYER_Y; yLevel <= PLAY_ARENA_Y + INITIAL_PLAYER_Y; yLevel += CUBE_SIZE_Y) { //
		for (int i = 0; i < cubes->size(); i++) {
			if (cubes->at(i).getState() == Cube::CubeState::INACTIVE){
				if (cubes->at(i).getPosition().y == yLevel) {
					for (int xLevel = INITIAL_PLAYER_X; xLevel < PLAY_ARENA_X + INITIAL_PLAYER_X; xLevel += CUBE_SIZE_X) { //
						if (cubes->at(i).getPosition().x == xLevel) {
							counter++;
							indexPlacementForCompletedRows.push_back(i);
						}
						if (counter == NUM_OF_COLUMNS) {
							height = yLevel;
							return true;
						}
					}
				}
			}
		}
		indexPlacementForCompletedRows.clear();
		counter = 0;
	}
	return false;
}

void Manager::undoAllActiveRuns() {
	for (int i = 0; i < cubes->size(); i++) {
		if (cubes->at(i).getState() == Cube::CubeState::ACTIVE) {
			cubes->at(i).undoRun();
		}
	}
}

void Manager::checkForGameOverAndSet() {
	for (int i = 0; i < cubes->size(); i++) {
		if (cubes->at(i).getState() == Cube::CubeState::INACTIVE && cubes->at(i).getPosition().y <= INITIAL_PLAYER_Y) { //
			gameState = GameState::OVER;
		}
		else {
			gameState = GameState::RUNNING;
		}
	}
}

void Manager::setAllCubesState(Cube::CubeState s) {
	for (int i = 0; i < cubes->size(); i++) {
		cubes->at(i).setState(s);
	}
	ghostCubes->clear();
}

void Manager::increaseSpeedThreshold(int level) {
	for (int i = 1; i < NUM_OF_LEVELS; i++) { // 
		if (level == i) {
			speedThreshold -= incrementThreshold;
		}
	}
}

void Manager::deleteRowsThatAreFull() {
	int rowDeleteCounter = 0;
	for (int i = cubes->size() - 1; i >= 0; i--) {
		for(int j = 0; j < indexPlacementForCompletedRows.size(); j++){
			if (i == indexPlacementForCompletedRows[j]) {
				cubes->erase(cubes->begin() + i);
				rowDeleteCounter++;
				if (rowDeleteCounter == NUM_OF_COLUMNS) {
    			deleteCounter++;
					rowDeleteCounter = 0;
				}
			}
		}
	}
}

void Manager::shiftAllDownWhenDeleted() {
	for (int i = 0; i < cubes->size(); i++) {
		if (cubes->at(i).getState() == Cube::CubeState::INACTIVE) {
			if (cubes->at(i).getPosition().y < height) {
				cubes->at(i).increasePosition(sf::Vector2f(0, cubes->at(i).getSize().y)); //
			}
		}
	}
}