#include "Rotation.h"

Rotation::Rotation(sf::Vector2f moveSize, sf::RenderWindow* window) {
	this->moveSize = moveSize;
	this->window = window;
	radius = 2; //this can be anything, I am using the middle as reference
	rotationPoint.setRadius(radius);
	rotationPoint.setOrigin(radius, radius);
}

void Rotation::setPosition(sf::Vector2f p) {
	rotationPos = p;
}

sf::Vector2f Rotation::getPosition() {
	return rotationPos;
}

void Rotation::moveUp() {
	rotationPos.y -= moveSize.y;
}

void Rotation::moveDown() {
	rotationPos.y += moveSize.y;
}

void Rotation::moveLeft() {
	rotationPos.x -= moveSize.x;
}

void Rotation::moveRight() {
	rotationPos.x += moveSize.x;
}

void Rotation::run() {
	rotationPoint.setPosition(rotationPos);
}

void Rotation::draw() {
	window->draw(rotationPoint);
}
