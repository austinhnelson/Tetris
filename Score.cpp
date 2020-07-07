#include "Score.h"
Score::Score() {
	score = numberOfLinesCleared = level = 0;
}

int Score::getNumberOfLinesCleared() {
	return numberOfLinesCleared;
}

int Score::getScore() {
	return score;
}

int Score::getLevel() {
	return level;
}

void Score::resets() {
	score = numberOfLinesCleared = level = 0;
}

void Score::increaseNumberOfLinesCleared(int i) {
	numberOfLinesCleared += i;
	if (i == 1) {
		score += 40;
	}
	else if (i == 2) {
		score += 100;
	}
	else if (i == 3) {
		score += 300;
	}
	else if (i == 4) {
		score += 1200;
	}
	for (int i = 0; i <= 100; i += 10) {
		if (numberOfLinesCleared == i) {
			level++;
		}
	}
}

