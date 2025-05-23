#include "InstructionsPage.h"
#include <iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
using namespace std;
using namespace sf;

InstructionsPage::InstructionsPage(const Font& font, const Vector2u& windowSize)
    : active(false) {
   
    if (!backgroundTexture.loadFromFile("assets/pics/bg.jpg")) {
        std::cerr << "Failed to load background!" << std::endl;
    }
    else {
        backgroundSprite.setTexture(backgroundTexture);

      

       Vector2u textureSize = backgroundTexture.getSize();
        backgroundSprite.setScale(
            1000.0f / textureSize.x,
            600.0f / textureSize.y
        );
    }
    backgroundOverlay.setSize(Vector2f(windowSize));
    backgroundOverlay.setFillColor(Color(0, 0, 0, 150));

  
    titleText.setFont(font);
    titleText.setCharacterSize(40);
    titleText.setFillColor(Color::Yellow);
    titleText.setPosition(250, 40); 
    titleText.setString("Instructions");

   
    instructionsText.setFont(font);
    instructionsText.setCharacterSize(20);
    instructionsText.setFillColor(Color::White);
    instructionsText.setPosition(50, 170);

    // Instruction content
    string instructions =
        "Welcome to Pac-Man!\n\n"
        "Use arrow keys to move Pac-Man.\n"
        "Eat all the dots and pellets to score points.\n"
        "Avoid the ghosts and don't get caught!\n\n"
        "Press Enter to return to the menu.";

    instructionsText.setString(instructions);

    tipText.setFont(font);
    tipText.setCharacterSize(18);
    tipText.setFillColor(Color::Cyan);
    tipText.setPosition(50, 450);
    tipText.setStyle(Text::Italic | Text::Bold);
    tipText.setString("Tip: You can always check the instructions from \n the menu.");
}

void InstructionsPage::render(RenderWindow& window) {
    if (active) {
        window.draw(backgroundSprite);

       
        window.draw(backgroundOverlay);

      
        window.draw(titleText);

        
        window.draw(instructionsText);
        
        window.draw(tipText);
    }
}

void InstructionsPage::handleInput(sf::Event& event) {
    if (active && event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Return) {
            active = false;
        }
    }
}

void InstructionsPage::setActive(bool active) {
    this->active = active;
}
