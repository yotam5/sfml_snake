

#ifndef GAME_H
#define GAME_H

//c++ libs
#include <vector>

//defenitions for screen
#define WIDTH 800
#define HEIGHT 600

//sfml libs
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Game
{
public:
    Game(); //constructor
    virtual ~Game(); //destructor

    //functions
    void update();
    void render();
    void pollEvents();
    void renderBodyParts(sf::RenderTarget &target);
    void updateBodyParts();
    const bool getEndGame() const;
    const bool isRunning() const;
private:
    //sfml stuff
    sf::RenderWindow* window;
    sf::Event event;
    sf::VideoMode vidoeMode;

    //helper functions
    void initVariables();
    void initWindow();

    //int
    int score;

    //boolean
    bool running;
    bool endGame;

    //vector
    std::vector<sf::RectangleShape> bodyParts;

};

#endif 