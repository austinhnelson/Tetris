#pragma once
#include <iostream>
#include <fstream>
#include "SFML/Graphics.hpp"
#include "Setup.h"

class HighScore
{
public:
	HighScore(sf::RenderWindow* window);
	void saveScore(int s);
	void writeScoresToFile();
	void resetHighScoreState();
	void setMessage(std::string s);
	void run();
	void draw();
private:
	sf::RenderWindow* window;
	sf::Vector2f popUpBoxLocation;
	sf::Text highScoreText, highScorePopUp;
	sf::Font font;
	std::vector<int> highScores;
	std::fstream highScoreFile;
	std::string highScoreFileName;
	bool highScoreState;
	void loadHighScore();
};

