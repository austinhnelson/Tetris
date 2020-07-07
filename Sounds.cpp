#include "Sounds.h"

Sounds::Sounds() {
	buffer.loadFromFile("ThemeMusic.wav");
	sound.setBuffer(buffer);
	sound.setVolume(30);
}

void Sounds::play() {
	if (sound.getStatus() != sf::Sound::Playing) {
		sound.play();
	}
}