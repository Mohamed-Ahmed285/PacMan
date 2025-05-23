#include "LoseMenu.h"
#include <iostream>

LoseMenu::LoseMenu(float width, float height, int score) {
    if (!font.loadFromFile("assets/fonts/Emulogic.otf")) {
        cerr << "Error loading font.\n";
    }
    if (!background.loadFromFile("assets/pics/bg.jpg"))
    {
        cerr << "Failed to load background!" << endl;
    }
    else
    {
        backgroundSprite.setTexture(background);

        // Scale background

        Vector2u textureSize = background.getSize();
        backgroundSprite.setScale(
            1000.0f / textureSize.x,
            600.0f / textureSize.y);
    }
    selectedIndex = 0;

    // Game Over Title
    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(60);
    gameOverText.setFillColor(sf::Color(193, 27, 23));
    gameOverText.setPosition(
        width / 2 - gameOverText.getGlobalBounds().width / 2,
        height / 5
    );

    // YOUR SCORE (white label)
    scoreLabelText.setFont(font);
    scoreLabelText.setString("YOUR SCORE ");
    scoreLabelText.setCharacterSize(30);
    scoreLabelText.setFillColor(sf::Color::White);

    // SCORE NUMBER (yellow)
    scoreValueText.setFont(font);
    scoreValueText.setCharacterSize(30);
    scoreValueText.setFillColor(sf::Color(255, 165, 0));

    setScore(score); // sets both scoreLabelText and scoreValueText positions

    // Menu Options
    std::string options[] = { "REPLAY", "MAIN MENU" };
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
    if (!music.openFromFile("assets/sounds/lose.ogg"))
    {
        cerr << "Failed to load lose music!" << std::endl;
    }
    else
    {
        music.setVolume(20);
    }
}

void LoseMenu::Musicp()
{
    music.play();
}

void LoseMenu::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    window.draw(gameOverText);
    window.draw(scoreLabelText);
    window.draw(scoreValueText);
    for (const auto& option : menuOptions) {
        window.draw(option);
    }
}

void LoseMenu::moveUp() {
    if (selectedIndex > 0) {
        menuOptions[selectedIndex].setFillColor(sf::Color::White);
        selectedIndex--;
        menuOptions[selectedIndex].setFillColor(sf::Color(255, 165, 0));
    }
}

void LoseMenu::moveDown() {
    if (selectedIndex < static_cast<int>(menuOptions.size()) - 1) {
        menuOptions[selectedIndex].setFillColor(sf::Color::White);
        selectedIndex++;
        menuOptions[selectedIndex].setFillColor(sf::Color(255, 165, 0));
    }
}

int LoseMenu::getSelectedIndex() const {
    return selectedIndex;
}

void LoseMenu::setScore(int score) {
    std::string scoreStr = std::to_string(score);
    scoreLabelText.setPosition(
        gameOverText.getPosition().x + 10,
        gameOverText.getPosition().y + 80
    );

    scoreValueText.setString(scoreStr);
    scoreValueText.setPosition(
        scoreLabelText.getPosition().x + scoreLabelText.getGlobalBounds().width + 5,
        scoreLabelText.getPosition().y
    );
}
