#include "Pieces.h"

Pieces::Pieces(sf::Vector2f position, sf::Vector2f size, std::vector<GhostCube>* ghostCubes, std::vector<Cube>* cubes, Rotation* rotation, sf::RenderWindow* window){
	srand(time(NULL));
	this->position = position;
	this->size = size;
	this->ghostCubes = ghostCubes;
	this->cubes = cubes;
	this->rotation = rotation;
	this->window = window;
	image.loadFromFile("Cube.png");
	texture.loadFromImage(image);
	//Setting the position of where the image is located in the file
	iBlockIntRect = sf::IntRect(394, 47, size.x, size.y);
	oBlockIntRect = sf::IntRect(99, 46, size.x, size.y);
	lBlockIntRect = sf::IntRect(509, 77, size.x, size.y);
	jBlockIntRect = sf::IntRect(285, 63, size.x, size.y);
	sBlockIntRect = sf::IntRect(176, 43, size.x, size.y);
	zBlockIntRect = sf::IntRect(6, 42, size.x, size.y);
	tBlockIntRect = sf::IntRect(578, 54, size.x, size.y);
	spawn();
}

block Pieces::getCurrentBlock() {
	return currentBlock;
}

void Pieces::run() {
	spawnPieceIfNoCubesAreActive();
}

void Pieces::selector() {
	currentBlock = static_cast<block>(rand() % BLOCK_SIZE);
}

void Pieces::spawn() {
	selector();
	if (currentBlock == block::I_BLOCK) {
		int numberOfCubesInFirstRow = 4;
		for (int i = 0; i < numberOfCubesInFirstRow; i++) {
			Cube cube(sf::Vector2f(position.x + (i * size.x), position.y), iBlockIntRect, &texture, rotation, window);
			GhostCube ghostCube(sf::Vector2f(position.x + (i * size.x), position.y), iBlockIntRect, &texture, rotation, window);
			cubes->push_back(cube);
			ghostCubes->push_back(ghostCube);
		}
		rotation->setPosition(sf::Vector2f(position.x + (size.x * 2), position.y + size.y));

	}
	else if (currentBlock == block::O_BLOCK) {
		int numberOfCubesInFirstRow = 2;
		for (int i = 0; i < 2; i++) {
			Cube cube(sf::Vector2f(position.x + (i * size.x), position.y + size.y), oBlockIntRect, &texture, rotation, window);
			GhostCube ghostCube(sf::Vector2f(position.x + (i * size.x), position.y + size.y), oBlockIntRect, &texture, rotation, window);
			cubes->push_back(cube);
			ghostCubes->push_back(ghostCube);
		}
		int numberOfCubesInSecondRow = 2;
		for (int i = 0; i < numberOfCubesInSecondRow; i++) {
			Cube cube(sf::Vector2f(position.x + (i * size.x), position.y), oBlockIntRect, &texture, rotation, window);
			GhostCube ghostCube(sf::Vector2f(position.x + (i * size.x), position.y), oBlockIntRect, &texture, rotation, window);
			cubes->push_back(cube);
			ghostCubes->push_back(ghostCube);
		}
		rotation->setPosition(sf::Vector2f(position.x + size.x, position.y + size.y));
	}
	else if (currentBlock == block::L_BLOCK) {
		int numberOfCubesInFirstRow = 3;
		for (int i = 0; i < numberOfCubesInFirstRow; i++) {
			Cube cube(sf::Vector2f(position.x + (i * size.x), position.y + size.y), lBlockIntRect, &texture, rotation, window);
			GhostCube ghostCube(sf::Vector2f(position.x + (i * size.x), position.y + size.y), lBlockIntRect, &texture, rotation, window);
			cubes->push_back(cube);
			ghostCubes->push_back(ghostCube);
		}
		int numberOfCubesInSecondRow = 1;
		for (int i = 0; i < numberOfCubesInSecondRow; i++) {
			Cube cube(position, lBlockIntRect, &texture, rotation, window);
			GhostCube ghostCube(position, lBlockIntRect, &texture, rotation, window);
			cubes->push_back(cube);
			ghostCubes->push_back(ghostCube);
		}
		rotation->setPosition(sf::Vector2f(position.x + (size.x) + (size.x / 2), position.y + (size.y) + (size.y / 2)));
	}
	else if (currentBlock == block::J_BLOCK) {
		int numberOfCubesInFirstRow = 3;
		for (int i = 0; i < numberOfCubesInFirstRow; i++) {
			Cube cube(sf::Vector2f(position.x + (i * size.x), position.y + size.y), jBlockIntRect, &texture, rotation, window);
			GhostCube ghostCube(sf::Vector2f(position.x + (i * size.x), position.y + size.y), jBlockIntRect, &texture, rotation, window);
			cubes->push_back(cube);
			ghostCubes->push_back(ghostCube);
		}
		int numberOfCubesInSecondRow = 1;
		for (int i = 0; i < numberOfCubesInSecondRow; i++) {
			Cube cube(sf::Vector2f(position.x + (2 * size.x), position.y), jBlockIntRect, &texture, rotation, window);
			GhostCube ghostCube(sf::Vector2f(position.x + (2 * size.x), position.y), jBlockIntRect, &texture, rotation, window);
			cubes->push_back(cube);
			ghostCubes->push_back(ghostCube);
		}
		rotation->setPosition(sf::Vector2f(position.x + (size.x) + (size.x / 2), position.y + (size.y) + (size.y / 2)));
	}
	else if (currentBlock == block::S_BLOCK) {
		int numberOfCubesInFirstRow = 2;
		for (int i = 0; i < numberOfCubesInFirstRow; i++) {
			Cube cube(sf::Vector2f(position.x + (i * size.x), position.y + size.y), sBlockIntRect, &texture, rotation, window);
			GhostCube ghostCube(sf::Vector2f(position.x + (i * size.x), position.y + size.y), sBlockIntRect, &texture, rotation, window);
			cubes->push_back(cube);
			ghostCubes->push_back(ghostCube);
		}
		int numberOfCubesInSecondRow = 2;
		for (int i = 1; i < numberOfCubesInSecondRow + 1; i++) { //added one so offset with allign with rest of cubes in the piece
			Cube cube(sf::Vector2f(position.x + (i * size.x), position.y), sBlockIntRect, &texture, rotation, window);
			GhostCube ghostCube(sf::Vector2f(position.x + (i * size.x), position.y), sBlockIntRect, &texture, rotation, window);
			cubes->push_back(cube);
			ghostCubes->push_back(ghostCube);
		}
		rotation->setPosition(sf::Vector2f(position.x + (size.x) + (size.x / 2), position.y + (size.y) + (size.y / 2)));
	}
	else if (currentBlock == block::Z_BLOCK) {
		int numberOfCubesInFirstRow = 2;
		for (int i = 1; i < numberOfCubesInFirstRow + 1; i++) { //added one so offset with allign with rest of cubes in the piece
			Cube cube(sf::Vector2f(position.x + (i * size.x), position.y + size.y), zBlockIntRect, &texture, rotation, window);
			GhostCube ghostCube(sf::Vector2f(position.x + (i * size.x), position.y + size.y), zBlockIntRect, &texture, rotation, window);
			cubes->push_back(cube);
			ghostCubes->push_back(ghostCube);
		}
		int numberOfCubesInSecondRow = 2;
		for (int i = 0; i < numberOfCubesInSecondRow; i++) {
			Cube cube(sf::Vector2f(position.x + (i * size.x), position.y), zBlockIntRect, &texture, rotation, window);
			GhostCube ghostCube(sf::Vector2f(position.x + (i * size.x), position.y), zBlockIntRect, &texture, rotation, window);
			cubes->push_back(cube);
			ghostCubes->push_back(ghostCube);
		}
		rotation->setPosition(sf::Vector2f(position.x + (size.x) + (size.x / 2), position.y + (size.y) + (size.y / 2)));
	}
	else if (currentBlock == block::T_BLOCK) {
		int numberOfCubesInFirstRow = 3;
		for (int i = 0; i < numberOfCubesInFirstRow; i++) {
			Cube cube(sf::Vector2f(position.x + (i * size.x), position.y + size.y), tBlockIntRect, &texture, rotation, window);
			GhostCube ghostCube(sf::Vector2f(position.x + (i * size.x), position.y + size.y), tBlockIntRect, &texture, rotation, window);
			cubes->push_back(cube);
			ghostCubes->push_back(ghostCube);
		}
		int numberOfCubesInSecondRow = 1;
		for (int i = 0; i < numberOfCubesInSecondRow; i++) {
			Cube cube(sf::Vector2f(position.x + size.x, position.y), tBlockIntRect, &texture, rotation, window);
			GhostCube ghostCube(sf::Vector2f(position.x + size.x, position.y), tBlockIntRect, &texture, rotation, window);
			cubes->push_back(cube);
			ghostCubes->push_back(ghostCube);
		}
		rotation->setPosition(sf::Vector2f(position.x + (size.x) + (size.x / 2), position.y + (size.y) + (size.y / 2)));
	}
}

void Pieces::spawnPieceIfNoCubesAreActive() {
	bool activeState;
	if (cubes->size() > 0) {
		for (int i = 0; i < cubes->size(); i++) {
			if (cubes->at(i).getState() == Cube::CubeState::INACTIVE) {
				activeState = false;
			}
			else {
				activeState = true;
				break;
			}
		}
	}
	else {
		activeState = false;
	}
	if (activeState == false) {
		spawn();
	}
}