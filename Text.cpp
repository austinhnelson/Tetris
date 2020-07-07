#include "Text.h"
Text::Text(Score* score, sf::RenderWindow* window) {
	this->window = window;
	this->score = score;
	font.loadFromFile("TetrisFont.TTF");
	levelText.setFont(font);
	scoreText.setFont(font);
}

void Text::run() {
	int level = score->getLevel();
	int playerScore = score->getScore();
	int offset = 10;

	levelText.setString("LEVEL: " + std::to_string(level));
	levelText.setPosition(sf::Vector2f(TEXT_BOX_ALLIGN_X + offset, INITIAL_PLAYER_Y + offset));

	scoreText.setString("SCORE: " + std::to_string(playerScore));
	scoreText.setPosition(sf::Vector2f(TEXT_BOX_ALLIGN_X + offset, INITIAL_PLAYER_Y + TEXT_BOX_COORD_OFFSET_Y + offset));
}

void Text::draw() {
	window->draw(levelText);
	window->draw(scoreText);
}