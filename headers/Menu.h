
#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <sstream>
#include <vector>

class Menu
{
public:
    Menu(float width, float height, std::vector<std::stringstream> menuTexts,
         int length = 3);
    ~Menu();

    void draw(sf::RenderTarget &target);
    void MoveUp();
    void MoveDown();
    int GetPressedItem() { return seletedItemIndex; }

private:
    void init(int length);
    int seletedItemIndex;
    sf::Font font;
    std::vector<sf::Text> menu;
};
