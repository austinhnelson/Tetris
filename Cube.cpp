#include "Cube.h"

Cube::Cube(sf::Vector2f position, sf::IntRect bodyIntRect, sf::Texture* texture, Rotation* rotation, sf::RenderWindow* window) {
	this->position = position;
	size.x = bodyIntRect.width;
	size.y = bodyIntRect.height;
	this->rotation = rotation;
	this->window = window;
	cubeState = CubeState::ACTIVE;
	body.setPosition(this->position);
	body.setTexture(*texture);
	body.setTextureRect(bodyIntRect);
}

sf::Vector2f Cube::getPosition() {
	return position;
}

sf::Vector2f Cube::getSize() {
	return size;
}

Cube::CubeState Cube::getState() {
	return cubeState;
}

void Cube::setPosition(sf::Vector2f position) {
	this->position = position;
}

void Cube::setState(Cube::CubeState cubeState) {
	this->cubeState = cubeState;
}

void Cube::increasePosition(sf::Vector2f position) {
	this->position += position; 
	body.setPosition(this->position);
}

void Cube::moveActiveUp() {
	if (cubeState == CubeState::ACTIVE) {
		increasePosition(sf::Vector2f(0, -size.y));
	}
}

void Cube::moveActiveDown() {
	if (cubeState == CubeState::ACTIVE) {
		increasePosition(sf::Vector2f(0, size.y));
	}
}

void Cube::moveActiveLeft() {
	if (cubeState == CubeState::ACTIVE) {
		increasePosition(sf::Vector2f(-size.x, 0));
	}
}

void Cube::moveActiveRight() {
	if (cubeState == CubeState::ACTIVE) {
		increasePosition(sf::Vector2f(size.x, 0));
	}
}

Cube::Quadrant Cube::checkCubeQuadrant(sf::Vector2f originPosition) {
	if (position.y >= originPosition.y && position.x >= originPosition.x) {
		quadrant = Quadrant::ONE;
	}
	else if (position.y >= originPosition.y && position.x < originPosition.x) {
		quadrant = Quadrant::TWO;
	}
	else if (position.y < originPosition.y && position.x < originPosition.x) {
		quadrant = Quadrant::THREE;
	}
	else if (position.y < originPosition.y && position.x >= originPosition.x) {
		quadrant = Quadrant::FOUR;
	}
	return quadrant;
}

void Cube::rotateActive() {
	float offset = 15;
	double relativeX, relativeY, relativeAngle, mag, angle, newX, newY;
	if (cubeState == CubeState::ACTIVE) {
		sf::Vector2f originPos = rotation->getPosition();
		sf::Vector2f tempCubePosition = sf::Vector2f(position.x + offset, position.y + offset);
		relativeX = originPos.x - tempCubePosition.x;
		relativeY = originPos.y - tempCubePosition.y;
		relativeAngle = relativeY / relativeX;
		if (relativeY == 0 && relativeX == 0) {
			relativeAngle = 0;
		}
		mag = sqrt(pow(relativeX, 2) + pow(relativeY, 2));
		quadrant = checkCubeQuadrant(originPos);
		if (quadrant == Quadrant::ONE) {
			angle = atan(relativeAngle) + (PI / 2);
		}
		else if (quadrant == Quadrant::TWO) {
			angle = atan(relativeAngle) + (PI) + (PI / 2);
		}
		else if (quadrant == Quadrant::THREE) {
			angle = atan(relativeAngle) + (PI) + (PI / 2);
		}
		else if (quadrant == Quadrant::FOUR) {
			angle = atan(relativeAngle) + (PI * 2) + (PI / 2);
		}
		newX = round(mag * cos(angle));
		newY = round(mag * sin(angle));
		position = sf::Vector2f(originPos.x + newX - offset, originPos.y + newY - offset);
		body.setPosition(sf::Vector2f(position));
	}
}

void Cube::undoRun() {
	position.y -= size.y;
	body.setPosition(position);
}

void Cube::draw() {
	window->draw(body);
}
