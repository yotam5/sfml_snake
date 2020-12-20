
#include "../headers/Game.h"

//constructor
Game::Game()
{
    this->initVariables();
    this->initWindow();
}

//destructor
Game::~Game()
{
    delete this->window;
}

//variable initialization
void Game::initVariables()
{
    this->window = nullptr;
    this->endGame = false;
    this->score = 0;

    //remove
    sf::RectangleShape tmp;
    tmp.setFillColor(sf::Color::Green);
    tmp.setSize(sf::Vector2f(15.f, 15.f));
    this->bodyParts.push_back(tmp);
    tmp.setFillColor(sf::Color::Blue);
    tmp.move(15.f, 0);
    this->bodyParts.push_back(tmp);
}

//initialization of the window
void Game::initWindow()
{
    this->vidoeMode.height = HEIGHT;
    this->vidoeMode.width = WIDTH;
    this->window = new sf::RenderWindow(this->vidoeMode, "Snake",
                                        sf::Style::Titlebar | sf::Style::Close);
    //init frame rate
    this->window->setFramerateLimit(60); //limit frame rate and make game playable
}

//render body parts
void Game::renderBodyParts(sf::RenderTarget &target)
{
    for (auto &part : this->bodyParts)
    {
        target.draw(part);
    }
}

//update body parts
void Game::updateBodyParts()
{
    for (auto &part : this->bodyParts)
    {
        part.move(1.f, 0);
    }
}

//update game
void Game::update()
{
    this->pollEvents();

    if (!this->getEndGame())
    {
        //logic
        updateBodyParts();
    }
}

//poll events
void Game::pollEvents()
{
    while (this->window->pollEvent(this->event))
    {
        sf::Event::EventType type = this->event.type;
        if(type == sf::Event::Closed)
        {
            this->window->close();
        }
        else if(event.key.code == sf::Keyboard::Up)
        {
            //do stuff
        }
    }
}

//get if game is running
const bool Game::isRunning() const
{
    return this->window->isOpen();
}

//return if game ended
const bool Game::getEndGame() const
{
    return this->endGame;
}

//render screen
void Game::render()
{
    this->window->clear();
    this->renderBodyParts(*this->window);
    this->window->display();
}
