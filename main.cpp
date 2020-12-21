#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

//user libs
#include "./src/Game.cpp"
#include "./src/Menu.cpp"

using namespace std;

//sfml libs
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
    vector<string> ops = {"Play", "Quit"};                          //game options
    Menu menu = Menu(game.getScreenWidth(), game.getScreenHeight(), //start menu screen
                     ops, game.getWindow());
    int res = -1;
    menu.run(res);
    if (res == 0) //handle Play
    {
        srand(time(NULL));
        while (game.isRunning() && !game.getEndGame())
        {
            game.update();
            game.render();
        }
        this_thread::sleep_for(chrono::seconds(4));
    }
    else //handle Quit
    {
        game.getWindow()->close();
    }
}
