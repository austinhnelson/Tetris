#include "HighScore.h"

HighScore::HighScore(sf::RenderWindow* window) {
	this->window = window;
	popUpBoxLocation = sf::Vector2f((PLAY_ARENA_X / 2) + (1.5 * INITIAL_PLAYER_X), (PLAY_ARENA_Y / 3));
	font.loadFromFile("TetrisFont.TTF");

	highScoreText.setFont(font);

	highScorePopUp.setFont(font);
	highScorePopUp.setFillColor(sf::Color::Red);
	highScorePopUp.setString("New High Score!!!");
	highScorePopUp.setPosition(sf::Vector2f(popUpBoxLocation.x - highScorePopUp.getLocalBounds().width / 2, popUpBoxLocation.y - (highScorePopUp.getLocalBounds().height / 2) - (TEXT_SIZE * 4)));

	highScoreFileName = "HighScore.txt";
	loadHighScore();
	highScoreState = false;
}

void HighScore::resetHighScoreState() {
	highScoreState = false;
}

void HighScore::loadHighScore() {
	highScoreFile.open(highScoreFileName);
	if (!highScoreFile.is_open()) {
		std::cout << "No High Scores\n";
		return;
	}
	std::string line;
	while (getline(highScoreFile, line)) {
		int score = std::stoi(line);
		highScores.push_back(score);
	}
	highScoreFile.close();
}

void HighScore::saveScore(int s) {
	if (highScores.size() == 0) {
		highScores.push_back(s);
		highScoreState = true;
	}
	for (int i = 0; i < highScores.size(); i++) {
		if (highScores[i] < s) {
   			highScores.insert(highScores.begin() + i, s);
			highScoreState = true;
			break;
		}
	}
	writeScoresToFile();
}

void HighScore::writeScoresToFile() {
	highScoreFile.open(highScoreFileName, std::ios::out);
	for (int i = 0; i < highScores.size(); i++) {
		highScoreFile << highScores[i] << std::endl;
	}
	highScoreFile.close();
}

void HighScore::setMessage(std::string s) {
	int offset = 10;
	highScoreText.setString(s);
	highScoreText.setPosition(sf::Vector2f(TEXT_BOX_ALLIGN_X + offset, INITIAL_PLAYER_Y + (2 * TEXT_BOX_COORD_OFFSET_Y) + offset));
}

void HighScore::run() {
	if (highScores.size() == 0) {
		setMessage("No HS!");
	}
	else {
		setMessage("HS: " + std::to_string(highScores[0]));
	}
}

void HighScore::draw() {
	window->draw(highScoreText);
	if (highScoreState) {
   		window->draw(highScorePopUp);
	}
}