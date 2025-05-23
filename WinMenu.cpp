#include "WinMenu.h"
#include <iostream>

WinMenu::WinMenu(float width, float height, int score) {
    if (!font.loadFromFile("assets/fonts/Emulogic.otf")) {
        std::cerr << "Error loading font.\n";
    }
    selectedIndex = 0;

    winnertext.setFont(font);
    winnertext.setString("YOU WIN!");
    winnertext.setCharacterSize(60);
    winnertext.setFillColor(Color(82, 208, 23)); // Bright green
    winnertext.setPosition(
        width / 2 - winnertext.getGlobalBounds().width / 2,
        height / 6
    );

    if (!backgroundTexture.loadFromFile("assets/pics/bg.jpg"))
    {
        cerr << "Failed to load background!" << endl;
    }
    else
    {
        backgroundSprite.setTexture(backgroundTexture);

        // Scale background

        sf::Vector2u textureSize = backgroundTexture.getSize();
        backgroundSprite.setScale(
            1000.0f / textureSize.x,
            600.0f / textureSize.y);
    }
    scoreLabelText.setFont(font);
    scoreLabelText.setString("YOUR SCORE ");
    scoreLabelText.setCharacterSize(30);
    scoreLabelText.setFillColor(sf::Color::White);

    // Score value - orange
    scoreValueText.setFont(font);
    scoreValueText.setCharacterSize(30);
    scoreValueText.setFillColor(sf::Color(255, 165, 0));

    setScore(score);  // Positions both scoreLabelText and scoreValueText

    // Menu Options
    std::string options[] = { "NEXT LEVEL", "MAIN MENU" };
    for (int i = 0; i < 2; ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(options[i]);
        text.setCharacterSize(30);
        text.setFillColor(i == 0 ? sf::Color(255, 165, 0) : sf::Color::White);
        text.setPosition(
            width / 2 - text.getGlobalBounds().width / 2,
            height / 2 + 80 + i * 50
        );
        menuOptions.push_back(text);
    }
}

void WinMenu::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    window.draw(winnertext);
    window.draw(scoreLabelText);
    window.draw(scoreValueText);
    for (const auto& option : menuOptions) {
        window.draw(option);
    }
}

void WinMenu::moveUp() {
    if (selectedIndex > 0) {
        menuOptions[selectedIndex].setFillColor(sf::Color::White);
        selectedIndex--;
        menuOptions[selectedIndex].setFillColor(sf::Color(255, 165, 0));
    }
}

void WinMenu::moveDown() {
    if (selectedIndex < static_cast<int>(menuOptions.size()) - 1) {
        menuOptions[selectedIndex].setFillColor(sf::Color::White);
        selectedIndex++;
        menuOptions[selectedIndex].setFillColor(sf::Color(255, 165, 0));
    }
}

int WinMenu::getSelectedIndex() const {
    return selectedIndex;
}

void WinMenu::setScore(int score) {
    std::string scoreStr = std::to_string(score);

    // Set label first
    scoreLabelText.setString("YOUR SCORE ");
    scoreLabelText.setPosition(
        winnertext.getPosition().x + 10,
        winnertext.getPosition().y + 80
    );

    // Set number
    scoreValueText.setString(scoreStr);
    scoreValueText.setPosition(
        scoreLabelText.getPosition().x + scoreLabelText.getGlobalBounds().width + 5,
        scoreLabelText.getPosition().y
    );
}