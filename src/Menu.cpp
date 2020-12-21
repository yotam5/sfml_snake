#include "../headers/Menu.h"
using namespace std;

Menu::Menu(int width, int height, vector<string> menuText,
           sf::RenderWindow *win,int textSize)
{
    this->menu.resize(menuText.size());
    this->seletedItemIndex = 0;
    this->window = win;
    if (!font.loadFromFile("./fonts/mrsmonster.ttf"))
    {
        std::cout << "Error: couldnt load fonts\n";
        exit(1);
    }

    int mul = 1;
    for (int i = 0; i < this->menu.size(); i++)
    {
        this->menu[i].setFont(this->font);
        this->menu[i].setCharacterSize(50);
        this->menu[i].setFillColor(sf::Color::White);
        this->menu[i].setString(menuText[i]);
        this->menu[i].setPosition(sf::Vector2f(width / DIVISOR,
                                               height / (menuText.size() + 1) * mul));
        mul += 1;
    }
}

void Menu::MoveUp()
{
    if (this->seletedItemIndex - 1 >= 0)
    {
        this->menu[seletedItemIndex].setFillColor(sf::Color::White);
        seletedItemIndex--;
        menu[seletedItemIndex].setFillColor(sf::Color::Green);
    }
}

void Menu::MoveDown()
{
    if (this->seletedItemIndex + 1 <= this->menu.size() - 1)
    {
        this->menu[seletedItemIndex].setFillColor(sf::Color::White);
        seletedItemIndex++;
        menu[seletedItemIndex].setFillColor(sf::Color::Green);
    }
}

//run menu
void Menu::run(int &save_res)
{
    bool press = false;
    while (window->isOpen() && !press)
    {
        while (window->pollEvent(event))

            switch (event.type)
            {
            case sf::Event::KeyReleased:
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    MoveUp();
                    break;

                case sf::Keyboard::Down:
                    MoveDown();
                    break;

                case sf::Keyboard::Return:
                    switch (GetPressedItem())
                    {
                    case 0:
                        save_res = 0;
                        press = true;

                        break;
                    case 1:
                        save_res = 1;
                        press = true;
                        break;
                    }
                    break;
                }
                break;
            }
        window->clear();
        draw(*this->window);
        window->display();
    }
}

Menu::~Menu()
{
}

void Menu::draw(sf::RenderTarget &target)
{
    for (int i = 0; i < this->menu.size(); i++)
    {
        target.draw(this->menu[i]);
    }
}