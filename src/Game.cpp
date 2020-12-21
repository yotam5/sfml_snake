
#include "../headers/Game.h"
#include <iostream>
//-----------------------
#include <vector>
#include <string>
using namespace std;

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

//init apple
void Game::initApple()
{
    float x = 100 + rand() % (WIDTH - 150);
    float y = 100 + rand() % (HEIGHT - 150);
    this->apple.setPosition(x, y);
}

//variable initialization
void Game::initVariables()
{
    this->window = nullptr;
    this->endGame = false;
    this->score = 0;

    //fonts and texts
    this->initFonts();
    this->initText();

    //apple color and coords
    this->apple.setFillColor(sf::Color::Red);
    this->initApple();
    apple.setSize(sf::Vector2f(15.f, 15.f));

    //directinon at the begining
    this->currentEventArrow = sf::Keyboard::Right;

    //init snake
    sf::RectangleShape tmp;
    tmp.setFillColor(sf::Color::Green);
    tmp.setSize(sf::Vector2f(15.f, 15.f));
    tmp.move(400.f, 10);
    this->bodyParts.push_back(tmp);
    tmp.setFillColor(sf::Color::Blue);
    tmp.setSize(sf::Vector2f(15.f, 15.f));
    for (int i = 0; i < INIT_SIZE; i++)
    {
        tmp.move(-15.f, 0);
        this->bodyParts.push_back(tmp);
    }
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

    //center
    auto desktop = sf::VideoMode::getDesktopMode();
    auto center = sf::Vector2i(desktop.width / 4, desktop.height / 4); //for center becuse it set top left
    window->setPosition(center);
}

//check if snake is outside screen
const bool Game::isOutsideScreen() const
{
    float x, y;
    for (auto &part : this->bodyParts)
    {
        x = part.getPosition().x;
        y = part.getPosition().y;
        if (x >= WIDTH || x <= 0)
        {
            return true;
        }
        if (y >= HEIGHT || y <= 0)
        {
            return true;
        }
    }
    return false;
}

//draw apple
void Game::drawApple(sf::RenderTarget &target)
{
    target.draw(apple);
}

//render body parts
void Game::renderBodyParts(sf::RenderTarget &target)
{
    for (auto &part : this->bodyParts)
    {
        target.draw(part);
    }
    target.draw(this->bodyParts[0]);
}

//check if head touch tail
const bool Game::isHeadInTail() const
{
    auto head = this->bodyParts[0];
    //the +20 is because the snake body is from a lot of cubes that
    //touch each other, if not like that when the snake make turns
    //it will move too fast to be playable.
    for (auto i = begin(this->bodyParts) + 20; i != end(this->bodyParts); i++)
    {
        if ((*i).getGlobalBounds().intersects(head.getGlobalBounds()))
        {
            return true;
        }
    }
    return false;
}

//check if game end with head in tail or outside screen
bool Game::endOfGame() const
{
    if (this->isOutsideScreen())
    {
        return true;
    }
    if (this->score >= 3 && this->isHeadInTail())
    {
        return true;
    }
    return false;
}

//update body parts location
void Game::updateBodyParts()
{

    auto headLocation = this->bodyParts[0].getPosition();
    this->bodyParts[0].move(this->xDir, this->yDir);
    for (int i = this->bodyParts.size(); i > 0; i--)
    {
        float x = this->bodyParts[i - 1].getPosition().x;
        float y = this->bodyParts[i - 1].getPosition().y;
        this->bodyParts[i].setPosition(x, y);
    }
    this->bodyParts[0].move(xDir, yDir);
}

//update game
void Game::update()
{

    this->pollEvents();
    this->endGame = this->endOfGame();
    if (!this->getEndGame())
    {
        //logic
        this->updateBodyParts();
        this->addPartToSnake();
        this->updateText();
    }
}

//set current event arrow keys
void Game::setCurrentEventArrow(sf::Keyboard::Key ev)
{
    this->currentEventArrow = ev; //need to make check
}

//return current event
const sf::Keyboard::Key Game::getCurrentEventArrow() const
{
    return this->currentEventArrow;
}

//void handle snake directions
void Game::handleDirections(sf::Event event)
{
    sf::Keyboard::Key eventCode = event.key.code;
    const sf::Keyboard::Key currentEv = this->getCurrentEventArrow();

    if (eventCode == sf::Keyboard::Up && currentEv != sf::Keyboard::Down)
    {
        this->setCurrentEventArrow(eventCode);
        this->yDir = -SPEED;
        this->xDir = 0.f;
    }
    else if (eventCode == sf::Keyboard::Right && currentEv != sf::Keyboard::Left)
    {
        this->setCurrentEventArrow(eventCode);
        this->yDir = 0.f;
        this->xDir = SPEED;
    }
    else if (eventCode == sf::Keyboard::Left && currentEv != sf::Keyboard::Right)
    {
        this->setCurrentEventArrow(eventCode);
        this->yDir = 0.f;
        this->xDir = -SPEED;
    }
    else if (eventCode == sf::Keyboard::Down && currentEv != sf::Keyboard::Up)
    {
        this->setCurrentEventArrow(eventCode);
        this->yDir = SPEED;
        this->xDir = 0.f;
    }
}

//poll events
void Game::pollEvents()
{
    while (this->window->pollEvent(this->event))
    {
        sf::Event::EventType type = this->event.type;
        if (type == sf::Event::Closed)
        {
            this->window->close();
        }

        handleDirections(event); //here
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

//handle score and if apple is eaten
void Game::handleScore()
{
    score += 1;
}

//check if apple is eaten
bool Game::checkAppleEaten()
{
    return apple.getGlobalBounds().intersects(this->bodyParts[0].getGlobalBounds());
}

//initiate fonts
void Game::initFonts()
{
    if (!this->font.loadFromFile("./fonts/mrsmonster.ttf"))
    {
        cout << "error, couldnt load font\n";
        exit(1);
    }
}

//ame update text
void Game::updateText()
{
    std::stringstream ss;
    ss << "Score: " << this->score << "\n";
    this->uiText.setString(ss.str());
}

//add part to snake and increase score&&re-initiate apple if so
void Game::addPartToSnake()
{
    if (checkAppleEaten())
    {
        this->handleScore();
        this->initApple();
        auto tmp = sf::RectangleShape();
        tmp.setFillColor(sf::Color::Blue);
        tmp.setSize(sf::Vector2f(15.f, 15.f));
        int length = this->bodyParts.size();
        auto posLast = this->bodyParts[length - 1].getPosition();
        int x_add = 0;
        int y_add = 0;
        if (this->xDir != 0)
        {
            x_add = (this->xDir > 0) ? -4 : 4;
        }
        else
        {
            y_add = (this->yDir > 0) ? -4 : 4;
        }
        for (int i = 0; i < 10; i++)
        {
            tmp.setPosition(posLast.x + x_add, posLast.y + y_add);
            posLast = tmp.getPosition();
            this->bodyParts.push_back(tmp);
        }
    }
}

//return window
sf::RenderWindow *Game::getWindow() const { return this->window; }

//get screen height
int Game::getScreenHeight() const { return HEIGHT; }

//get screen width
int Game::getScreenWidth() const { return WIDTH; }

//check if game ended with touch tail or out of screen

//render text
void Game::renderText(sf::RenderTarget &target)
{
    target.draw(this->uiText);
}

//init text
void Game::initText()
{
    this->uiText.setFont(font);
    this->uiText.setCharacterSize(30);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("None");
    this->uiText.move(360, 0);
}

//render screen
void Game::render()
{
    this->window->clear();
    this->renderBodyParts(*this->window);
    this->drawApple(*this->window);
    this->renderText(*this->window);
    this->window->display();
}
