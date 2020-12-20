#include "../headers/Menu.h"
using namespace std;

Menu::Menu(float width, float height, vector<stringstream> menuText, int length)
{
    this->init(length);
    if (!font.loadFromFile("./fonts/mrsmonster.ttf"))
    {
        std::cout << "Error: couldnt load fonts\n";
        exit(1);
    }

    int mul = 1;
    for (int i = 0; i < this->menu.size(); i++)
    {
        this->menu[i].setFont(this->font);
        this->menu[i].setFillColor(sf::Color::White);
        this->menu[i].setString(menuText[i].str());
        this->menu[i].setPosition(sf::Vector2f(width / 2, 
            height / (menuText.size() + 1) * mul));
        mul += 1;
    }
}

void Menu::MoveUp()
{
    if(this->seletedItemIndex - 1 >= 0)
    {
        this->menu[seletedItemIndex].setFillColor(sf::Color::White);
        seletedItemIndex--;
        menu[seletedItemIndex].setFillColor(sf::Color::Green);
    }
}

void Menu::MoveDown()
{
    if(this->seletedItemIndex + 1 <= this->menu.size())
    {
        this->menu[seletedItemIndex].setFillColor(sf::Color::White);
        seletedItemIndex++;
        menu[seletedItemIndex].setFillColor(sf::Color::Green);
    }
}

void Menu::init(int length)
{
    this->menu.resize(length);
    this->seletedItemIndex = 0;
}

Menu::~Menu()
{
}

void Menu::draw(sf::RenderTarget &target)
{
    for(int i =0 ;i < this->menu.size();i++)
    {
        target.draw(this->menu[i]);
    }
}