

#ifndef GAME_H
#define GAME_H

//c++ libs
#include <vector>
#include <sstream>

//defenitions for screen
#define WIDTH 800
#define HEIGHT 600
#define INIT_SIZE 10 //initial snake size
#define SPEED 1.2 //speed

//sfml libs
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Game
{
public:
    Game();          //constructor
    virtual ~Game(); //destructor

    //functions

    //update events
    void update();

    //render 
    void render();

    //handle event from keyboard etc
    void pollEvents();

    //render snake
    void renderBodyParts(sf::RenderTarget &target);

    //update snake 
    void updateBodyParts();

    //return if game end bool
    const bool getEndGame() const;

    //return if game running, sfml window
    const bool isRunning() const;

    //return the current arrow key used
    const sf::Keyboard::Key getCurrentEventArrow() const;

    //set current arrow key
    void setCurrentEventArrow(sf::Keyboard::Key);

    //draw/render apple
    void drawApple(sf::RenderTarget &target);

    ///check if apple is eaten
    bool checkAppleEaten();

    //increase score
    void handleScore();

    //return bool of is out of screen
    const bool isOutsideScreen() const;

    //check if head touch tail
    const bool isHeadInTail() const;

    //update text
    void updateText();

    //render text
    void renderText(sf::RenderTarget &target);

    //check if game ended with touch tail or out of screen
    bool endOfGame() const;

private:
    //widow stuff
    sf::RenderWindow *window;
    sf::VideoMode vidoeMode;

    //event stuff
    sf::Event event;

    //text && fonts
    sf::Font font;
    sf::Text uiText;

    //helper functions
    void handleDirections(sf::Event);
    void addPartToSnake();

    //initiation
    void initApple();
    void initVariables();
    void initWindow();
    void initFonts();
    void initText();

    //current event
    sf::Keyboard::Key currentEventArrow;

    //int
    int score;

    //snake directions
    float xDir = 0;
    float yDir = 0;

    //apple coords
    sf::RectangleShape apple;

    //boolean
    bool running;
    bool endGame;

    //vector of snake body parts
    std::vector<sf::RectangleShape> bodyParts;
};

#endif