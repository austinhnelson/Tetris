#include "Map.h"

Map::Map(sf::RenderWindow* window) {
	this->window = window;
	scale = sf::Vector2f(1.15, 1.15);
	textBoxCoords = sf::IntRect(0, 0, 140, 49);
	iconImage.loadFromFile("TetrisLogo.png");
	this->window->setIcon(iconImage.getSize().x, iconImage.getSize().y, iconImage.getPixelsPtr());

	backgroundImage.loadFromFile("TetrisFullBackground.png");
	backgroundTexture.loadFromImage(backgroundImage);
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setTextureRect(sf::IntRect(0, 0, WINDOW_X, WINDOW_Y));
	sprites.push_back(backgroundSprite);

	gridImage.loadFromFile("TetrisGrid.jpg");
	gridTexture.loadFromImage(gridImage);
	gridSprite.setTexture(gridTexture);
	gridSprite.setTextureRect(sf::IntRect(95, 95, 311, 610)); //coordinates of grid image in file
	gridSprite.setColor(sf::Color(134, 15, 134, 240)); //setting custom color
	gridSprite.setPosition(sf::Vector2f(GRID_IMAGE_START_X, GRID_IMAGE_START_Y));
	sprites.push_back(gridSprite);

	textBoxImage.loadFromFile("TetrisLogoForText.png");
	textBoxImage.createMaskFromColor(sf::Color::White);
	textBoxTexture.loadFromImage(textBoxImage);

	levelSprite.setTexture(textBoxTexture);
	levelSprite.setScale(sf::Vector2f(scale));
	levelSprite.setColor(sf::Color::Yellow);
	levelSprite.setTextureRect(textBoxCoords);
	levelSprite.setPosition(TEXT_BOX_ALLIGN_X, INITIAL_PLAYER_Y);
	sprites.push_back(levelSprite);

	scoreSprite.setTexture(textBoxTexture);
	scoreSprite.setScale(sf::Vector2f(scale));
	scoreSprite.setColor(sf::Color::Yellow);
	scoreSprite.setTextureRect(textBoxCoords);
	scoreSprite.setPosition(sf::Vector2f(TEXT_BOX_ALLIGN_X, INITIAL_PLAYER_Y + textBoxCoords.height + CUBE_SIZE_Y));
	sprites.push_back(scoreSprite);

	highScoreSprite.setTexture(textBoxTexture);
	highScoreSprite.setScale(sf::Vector2f(scale));
	highScoreSprite.setColor(sf::Color::Yellow);
	highScoreSprite.setTextureRect(textBoxCoords);
	highScoreSprite.setPosition(sf::Vector2f(TEXT_BOX_ALLIGN_X, INITIAL_PLAYER_Y + (2 * textBoxCoords.height) + (2 * CUBE_SIZE_Y)));
	sprites.push_back(highScoreSprite);
}

void Map::draw() {
	for (int i = 0; i < sprites.size(); i++) {
		window->draw(sprites[i]);
	}
}