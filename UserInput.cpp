#include "UserInput.h"
#include <Windows.h>

UserInput::UserInput(std::vector<Cube>* cubes, Manager* manager, MenuStart* menu, Pieces* pieces, Rotation* rotation, Sounds* sound, sf::RenderWindow* window) {
	this->cubes = cubes;
	this->manager = manager;
	this->menu = menu;
	this->pieces = pieces;
	this->rotation = rotation;
	this->sound = sound;
	this->window = window;
}

void UserInput::getInput(sf::Event* event) {
	if(manager->getState() == Manager::GameState::RUNNING){
		if (event->type == sf::Event::KeyPressed) {
			if (event->key.code == sf::Keyboard::Left || event->key.code == sf::Keyboard::A) {
				moveCubeAndRotationLeft();
				checkPositionIsOpenAndMoveRight();
				manager->dropGhostPiece();
			}
			if (event->key.code == sf::Keyboard::Right || event->key.code == sf::Keyboard::D) {
				moveCubeAndRotationRight();
				checkPositionIsOpenAndMoveLeft();
				manager->dropGhostPiece();
			}
			if (event->key.code == sf::Keyboard::Down || event->key.code == sf::Keyboard::S) {
				moveCubeAndRotationDown();
				manager->dropGhostPiece();
			}
			if (event->key.code == sf::Keyboard::Up || event->key.code == sf::Keyboard::W) {
				rotateCubes();
				checkRotateIsCollidedWithLeftWall();
				checkRotateIsCollidedWithRightWall();
			}
			if (event->key.code == sf::Keyboard::Space) {
				dropGhostPieceAndCubesWithSpace();
			}
		}
	}
	if (manager->getState() == Manager::GameState::OVER) {
		if (event->type == sf::Event::KeyPressed) {
			if (event->key.code == sf::Keyboard::Enter) {
				manager->resetAndRestart();
			}
		}
	}
	if (manager->getState() == Manager::GameState::START) {
		if (event->type == sf::Event::KeyReleased) {
			switch (event->key.code) {
			case sf::Keyboard::Up:
				menu->moveUp();
				break;
			case sf::Keyboard::Down:
				menu->moveDown();
				break;
			case sf::Keyboard::Space:
				if (manager->getState() == Manager::GameState::START) {
					switch (menu->GetPressedItem()) {
					case 0:
						manager->setState(Manager::GameState::RUNNING);
						break;
					case 1:
						ShellExecute(NULL, "open", "https://www.cs.cornell.edu/boom/1999sp/projects/tetris/whatis.html", 
									 NULL, NULL, SW_SHOWNORMAL);
						break;
					case 2:
						window->close();
						break;
					}
					break;
				}
			}
		}
	}
	if (event->type == sf::Event::Closed) {
		window->close();
	}
}

void UserInput::moveCubeAndRotationLeft() {
	for (int i = 0; i < cubes->size(); i++) {
		cubes->at(i).moveActiveLeft();
	}
	rotation->moveLeft();
}

void UserInput::moveCubeAndRotationRight() {
	for (int i = 0; i < cubes->size(); i++) {
		cubes->at(i).moveActiveRight();
	}
	rotation->moveRight();
}

void UserInput::moveCubeAndRotationDown() {
	for (int i = 0; i < cubes->size(); i++) {
		cubes->at(i).moveActiveDown();
	}
	rotation->moveDown();
}

void UserInput::rotateCubes() {
	for (int i = 0; i < cubes->size(); i++) {
		cubes->at(i).rotateActive();
	}
}

void UserInput::checkPositionIsOpenAndMoveRight() {
	if (manager->anyCubesCollided() || manager->areCubesCollidedWithWall()) {
		for (int i = 0; i < cubes->size(); i++) {
			cubes->at(i).moveActiveRight();
		}
		rotation->moveRight();
	}
}

void UserInput::checkPositionIsOpenAndMoveLeft() {
	if (manager->anyCubesCollided() || manager->areCubesCollidedWithWall()) {
		for (int i = 0; i < cubes->size(); i++) {
			cubes->at(i).moveActiveLeft();
		}
		rotation->moveLeft();
	}
}

void UserInput::checkRotateIsCollidedWithLeftWall() {
	while (manager->areCubesCollidedWithLeftWall()) {
		for (int i = 0; i < cubes->size(); i++) {
			cubes->at(i).moveActiveRight();
		}
		rotation->moveRight();
	}
}

void UserInput::checkRotateIsCollidedWithRightWall() {
	while (manager->areCubesCollidedWithRightWall()) {
		for (int i = 0; i < cubes->size(); i++) {
			cubes->at(i).moveActiveLeft();
		}
		rotation->moveLeft();
	}
}

void UserInput::dropGhostPieceAndCubesWithSpace() {
	if (manager->getState() == Manager::GameState::RUNNING) {
		while (!manager->anyCubesCollided() && !manager->anyActiveCubesOnGround()) {
			for (int i = 0; i < cubes->size(); i++) {
				if (cubes->at(i).getState() == Cube::CubeState::ACTIVE) {
					cubes->at(i).increasePosition(sf::Vector2f(0, 30));
				}
			}
			rotation->moveDown();
		}
		while (manager->anyCubesCollided() || manager->anyActiveCubesOnGround()) {
			for (int i = 0; i < cubes->size(); i++) {
				if (cubes->at(i).getState() == Cube::CubeState::ACTIVE) {
					cubes->at(i).moveActiveUp();
					cubes->at(i).setState(Cube::CubeState::INACTIVE);
				}
			}
			manager->eraseAllGhosts();
			rotation->moveUp();
		}
	}
}
