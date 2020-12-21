#include <iostream>
#include <string>
#include <vector>
#include "./src/Game.cpp"
#include "./src/Menu.cpp"

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
    vector<string> ops = {"Play", "Quite"};
    Menu menu = Menu(game.getScreenWidth(), game.getScreenHeight(),
                     ops, game.getWindow());
    int res = -1;
    menu.run(res);
    if (res == 0) //Play
    {
        srand(time(NULL));
        while (game.isRunning() && !game.getEndGame())
        {
            game.update();
            game.render();
        }
    }
    else
    {
        game.getWindow()->close();
    }
}