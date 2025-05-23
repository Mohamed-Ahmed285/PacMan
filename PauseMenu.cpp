#include "PauseMenu.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace std;
using namespace sf;

PauseMenu::PauseMenu(float width, float height)
{
    if (!font.loadFromFile("assets/fonts/Emulogic.otf"))
    {
        std::cerr << "Error loading font.\n";
    }

    title.setFont(font);
    title.setString("PAUSED");
    title.setCharacterSize(40);
    title.setFillColor(sf::Color(255, 165, 0));
    title.setPosition(width / 2 - title.getGlobalBounds().width / 2, height / 2 - 150);

    // Setup menu options
    std::string options[2] = {"Resume", "Exit to Menu"};
    for (int i = 0; i < 2; ++i)
    {
        menu[i].setFont(font);
        menu[i].setCharacterSize(20);
        menu[i].setString(options[i]);
        menu[i].setFillColor(i == 1 ? sf::Color::White : sf::Color(255, 215, 0));
        menu[i].setPosition(width / 2 - menu[i].getGlobalBounds().width / 2, height / 2 + i * 50);
    }

    selectedItemIndex = 0;

    background.setSize(sf::Vector2f(400, 250));
    background.setFillColor(sf::Color(0, 0, 0, 230)); // semi-transparent black
    background.setPosition(width / 2 - background.getSize().x / 2, height / 2 - 170);
}

void PauseMenu::draw(RenderWindow &window)
{
    window.draw(background);
    window.draw(title);
    for (auto &item : menu)
        window.draw(item);
}

void PauseMenu::moveUp()
{
    
    
        menu[selectedItemIndex].setFillColor(sf::Color(200, 200, 200));
        selectedItemIndex = (selectedItemIndex-1 + 2) % 2;
        menu[selectedItemIndex].setFillColor(Color{ 255, 215, 0 });
    
}

void PauseMenu::moveDown()
{
    
        menu[selectedItemIndex].setFillColor(sf::Color(200, 200, 200));
        selectedItemIndex = (selectedItemIndex + 1) % 2;
        menu[selectedItemIndex].setFillColor(Color{ 255, 215, 0 });
   
}

int PauseMenu::getSelectedIndex() const
{
    return selectedItemIndex;
}