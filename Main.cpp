#include <cstdlib>
#include "SFML/Graphics.hpp"
#include "Windows.h"
#include "Cube.h"
#include "GameOver.h"
#include "GhostCube.h"
#include "HighScore.h"
#include "Manager.h"
#include "Map.h"
#include "MenuStart.h"
#include "Pieces.h"
#include "Rotation.h"
#include "Score.h"
#include "Setup.h"
#include "Sounds.h"
#include "Text.h"
#include "UserInput.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "Tetris");
    std::vector<Cube> cubes;
    std::vector<GhostCube> ghostCubes;
    MenuStart menu(sf::Vector2f(WINDOW_X, WINDOW_Y), &window);
    Rotation rotate(sf::Vector2f(CUBE_SIZE_X, CUBE_SIZE_Y), &window);
    Score score;
    Sounds sound;
    Text text(&score, &window);
    GameOver gameOver(&score, &window);
    HighScore highScore(&window);
    Pieces pieces(sf::Vector2f(INITIAL_PLAYER_X, INITIAL_PLAYER_Y), sf::Vector2f(CUBE_SIZE_X, CUBE_SIZE_Y), &ghostCubes, &cubes, &rotate, &window);
    Map map(&window);
    Manager manager(&cubes, &gameOver, &ghostCubes, &highScore, &map, &menu, &pieces, &rotate, &score, &sound, &text, &window);
    UserInput userInput(&cubes, &manager, &menu, &pieces, &rotate, &sound, &window);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            userInput.getInput(&event);
        }
        window.clear(sf::Color::White);
        manager.run();
        manager.draw();
        window.display();
    }
    return 0;
}