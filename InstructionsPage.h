#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class InstructionsPage {
public:
    InstructionsPage(const sf::Font& font, const sf::Vector2u& windowSize);
    void render(sf::RenderWindow& window);
    void handleInput(sf::Event& event);
    void setActive(bool active);

private:
    bool active;
    Text titleText;
    Text instructionsText;
    Text tipText;
    RectangleShape backgroundOverlay;
    Texture backgroundTexture;
    Sprite backgroundSprite;
};
