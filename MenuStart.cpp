#include "MenuStart.h"

MenuStart::MenuStart(sf::Vector2f size, sf::RenderWindow* window) {
	this->window = window;
	titleSize = 50;
	selectedSize = 35;
	titleYLevelOffset = 200;
	titleBoxYLevelOffset = 185;
	itemYLevelOffset = 50;
	optionBoxYLevelOffset = 75;
	optionShaderBoxYLevelOffset = 75;
	selectedItem = 0;
	titleBoxSize = sf::Vector2f(200, 85);
	optionBoxSize = sf::Vector2f(200, 200);
	optionBoxShaderSize = sf::Vector2f(220, 220);
	grey = sf::Color(147, 127, 123);
	orange = sf::Color(255, 165, 0);
	startScreenImage.loadFromFile("TetrisStartScreen.png");
	startScreenTexture.loadFromImage(startScreenImage);
	startScreenSprite.setTexture(startScreenTexture);
	startScreenSprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y));

	tetrisFont.loadFromFile("TetrisFont.TTF");
	titleText.setFont(tetrisFont);
	titleText.setCharacterSize(titleSize);
	titleText.setFillColor(sf::Color(255, 165, 0)); //orange color
	titleText.setString("Tetris!");
	titleText.setPosition(sf::Vector2f((size.x / 2) - (titleText.getLocalBounds().width / 2), (size.y / 2) - (titleText.getLocalBounds().height / 2) - titleYLevelOffset));

	text[0].setFont(tetrisFont);
	text[0].setCharacterSize(selectedSize);
	text[0].setFillColor(sf::Color(255, 165, 0)); //orange color
	text[0].setString("Play");
	text[0].setPosition(sf::Vector2f((size.x / 2) - (text[0].getLocalBounds().width / 2), (size.y / 2) - (text[0].getLocalBounds().height / 2)));

	text[1].setFont(tetrisFont);
	text[1].setFillColor(sf::Color(147, 127, 123)); //grey color
	text[1].setString("How To Play");
	text[1].setPosition(sf::Vector2f((size.x / 2) - (text[1].getLocalBounds().width / 2), (size.y / 2) - (text[1].getLocalBounds().height / 2) + itemYLevelOffset));

	text[2].setFont(tetrisFont);
	text[2].setFillColor(sf::Color(147, 127, 123)); //grey color
	text[2].setString("Quit");
	text[2].setPosition(sf::Vector2f((size.x / 2) - (text[2].getLocalBounds().width / 2), (size.y / 2) - (text[2].getLocalBounds().height / 2) + (2 * itemYLevelOffset)));

	titleBox.setSize(titleBoxSize);
	titleBox.setOrigin(sf::Vector2f(titleBox.getSize().x / 2, titleBox.getSize().y / 2));
	titleBox.setPosition(sf::Vector2f(size.x / 2, size.y / 2 - titleBoxYLevelOffset));
	titleBox.setFillColor(sf::Color(50, 50, 25, 60)); //dark color
	boxes.push_back(titleBox);

	optionBox.setSize(optionBoxSize);
	optionBox.setOrigin(sf::Vector2f(optionBox.getSize().x / 2, optionBox.getSize().y / 2));
	optionBox.setPosition(sf::Vector2f((size.x / 2), (size.y / 2) + optionBoxYLevelOffset));
	optionBox.setFillColor(sf::Color(139, 0, 139, 60)); //dark color
	boxes.push_back(optionBox);

	optionBoxShader.setSize(optionBoxShaderSize);
	optionBoxShader.setOrigin(sf::Vector2f(optionBoxShader.getSize().x / 2, optionBoxShader.getSize().y / 2));
	optionBoxShader.setPosition(sf::Vector2f((size.x / 2), (size.y / 2) + optionShaderBoxYLevelOffset));
	optionBoxShader.setFillColor(sf::Color(50, 50, 25, 60)); //dark color
	boxes.push_back(optionBoxShader);
}

void MenuStart::moveUp() {
	if (selectedItem - 1 >= 0) {
		text[selectedItem].setFillColor(grey);
		text[selectedItem].setCharacterSize(TEXT_SIZE);
		selectedItem--;
		text[selectedItem].setFillColor(orange);
		text[selectedItem].setCharacterSize(selectedSize);
	}
}

void MenuStart::moveDown() {
	if (selectedItem + 1 < MAX_NUMBER_OF_ITEMS) {
		text[selectedItem].setFillColor(grey); 
		text[selectedItem].setCharacterSize(TEXT_SIZE);
		selectedItem++;
		text[selectedItem].setFillColor(orange);
		text[selectedItem].setCharacterSize(selectedSize);
	}
}

void MenuStart::draw() {
	window->draw(startScreenSprite);
	for (int i = 0; i < boxes.size(); i++) {
		window->draw(boxes[i]);
	}
	window->draw(titleText);
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		window->draw(text[i]);
	}
}

int MenuStart::GetPressedItem() {
	return selectedItem;
}