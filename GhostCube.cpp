#include "GhostCube.h"

GhostCube::GhostCube(sf::Vector2f position, sf::IntRect bodyIntRect, sf::Texture* texture, Rotation* rotation, sf::RenderWindow* window) {
	this->position = position;
	size.x = bodyIntRect.width;
	size.y = bodyIntRect.height;
	this->rotation = rotation;
	this->window = window;
	body.setColor(sf::Color(255, 255, 255, 40));
	body.setPosition(this->position);
	body.setTexture(*texture);
	body.setTextureRect(bodyIntRect);
}

sf::Vector2f GhostCube::getPosition() {
	return position;
}

sf::Vector2f GhostCube::getSize() {
	return size;
}

void GhostCube::setPosition(sf::Vector2f p) {
	position = p;
	body.setPosition(position);
}

void GhostCube::increasePosition(sf::Vector2f p) {
	position += p;
	body.setPosition(position);
}

void GhostCube::draw() {
	window->draw(body);
}