#include <iostream>
#include "./src/Game.cpp"


using namespace std;

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/*
    NOTE: compile: g++ main.cpp -o sfml-app.o -lsfml-graphics -lsfml-window -lsfml-system
*/

int main()
{
    Game game;
    
    srand(time(NULL));
    while(game.isRunning() && !game.getEndGame())
    {
        game.update();
        game.render();
    }
}