#include <iostream>

#include "./src/Game.cpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/*
    NOTE: compile: g++ main.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
*/

int main()
{
    Game game;
    while(game.isRunning() && !game.getEndGame())
    {
        game.update();
        game.render();
    }
}