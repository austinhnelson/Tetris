#pragma once
#include <iostream>
#include "SFML/Audio.hpp"
class Sounds
{
public:
	Sounds();
	void play();
private:
	sf::SoundBuffer buffer;
	sf::Sound sound;
};

