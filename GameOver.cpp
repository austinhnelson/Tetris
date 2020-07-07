#include "GameOver.h"
GameOver::GameOver(Score* score, sf::RenderWindow* window) {
	this->score = score;
	this->window = window;
	defaultCharacterSize = 30;
	font.loadFromFile("TetrisFont.TTF");
	sizeOffset = sf::Vector2f(10, 20);
	gameOverBoxSize = sf::Vector2f(400, 150);
	gameOverBoxShaderSize = sf::Vector2f(gameOverBoxSize.x + sizeOffset.x, gameOverBoxSize.y + sizeOffset.y);

	gameOverBox.setFillColor(sf::Color(152, 24, 53, 180)); //setting fill color to grey RGB code
	gameOverBox.setSize(gameOverBoxSize);
	gameOverBox.setOrigin(gameOverBox.getSize().x / 2, gameOverBox.getSize().y / 2);
	gameOverBox.setPosition(sf::Vector2f((PLAY_ARENA_X / 2) + (1.5 * INITIAL_PLAYER_X), (PLAY_ARENA_Y / 3))); //custom location

	gameOverBoxShader.setFillColor(sf::Color(0, 0, 0, 180)); //setting fill color to black RGB code
	gameOverBoxShader.setSize(gameOverBoxShaderSize);
	gameOverBoxShader.setOrigin(gameOverBoxShader.getSize().x / 2, gameOverBoxShader.getSize().y / 2);
	gameOverBoxShader.setPosition(sf::Vector2f((PLAY_ARENA_X / 2) + (1.5 * INITIAL_PLAYER_X), (PLAY_ARENA_Y / 3))); //custom location

	gameOverText.setFont(font);

	playAgainText.setFont(font);

	gameOverScoreText.setFont(font);
}

void GameOver::run() {
	int playerScore = score->getScore();

	gameOverText.setString("GAME OVER!!");
	gameOverText.setPosition(sf::Vector2f(gameOverBox.getPosition().x - gameOverText.getLocalBounds().width / 2, gameOverBox.getPosition().y - (gameOverText.getLocalBounds().height / 2) - (defaultCharacterSize * 2)));

	gameOverScoreText.setString("Final Score: " + std::to_string(playerScore));
	gameOverScoreText.setPosition(sf::Vector2f(gameOverBox.getPosition().x - gameOverScoreText.getLocalBounds().width / 2, gameOverBox.getPosition().y - (gameOverScoreText.getLocalBounds().height / 2) - (defaultCharacterSize / 2)));

	playAgainText.setString("Press Enter To Play Again!");
	playAgainText.setPosition(sf::Vector2f(gameOverBox.getPosition().x - playAgainText.getLocalBounds().width / 2, gameOverBox.getPosition().y - (playAgainText.getLocalBounds().height / 2) + defaultCharacterSize));
}

void GameOver::draw() {
	window->draw(gameOverBoxShader);
	window->draw(gameOverBox);

	window->draw(gameOverText);
	window->draw(gameOverScoreText);
	window->draw(playAgainText);
}