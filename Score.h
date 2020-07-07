#pragma once
#include "SFML/Graphics.hpp"
class Score
{
public:
	Score();
	int getNumberOfLinesCleared();
	int getScore();
	int getLevel();
	void resets();
	void increaseNumberOfLinesCleared(int i);
private:
	int numberOfLinesCleared, score, level;
};

