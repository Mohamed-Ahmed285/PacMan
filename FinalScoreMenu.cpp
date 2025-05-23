#include "FinalScoreMenu.h"
#include <iostream>


FinalScoreMenu::FinalScoreMenu(float width, float height, int finalScore)
    : selectedIndex(0)
{
    if (!font.loadFromFile("assets/fonts/Emulogic.otf")) {
        cerr << "Error loading font\n";
    }
    if (!background.loadFromFile("assets/pics/bg.jpg"))
    {
        cerr << "Failed to load background!" << endl;
    }
    else
    {
        backgroundSprite.setTexture(background);

        // Scale background

        sf::Vector2u textureSize = background.getSize();
        backgroundSprite.setScale(
            1000.0f / textureSize.x,
            600.0f / textureSize.y);
    }

    // Title: CONGRATULATIONS!
    titleText.setFont(font);
    titleText.setString("CONGRATULATIONS!");
    titleText.setCharacterSize(60);
    titleText.setFillColor(Color(82, 208, 23));
    titleText.setPosition(width / 2 - titleText.getGlobalBounds().width / 2, height / 8);


    subtitleText.setFont(font);
    subtitleText.setString("You've completed the game!");
    subtitleText.setCharacterSize(26);
    subtitleText.setFillColor(Color::White);
    subtitleText.setPosition(width / 2 - subtitleText.getGlobalBounds().width / 2, height / 4);


    scoreLabelText.setFont(font);
    scoreLabelText.setString("FINAL SCORE:");
    scoreLabelText.setCharacterSize(36);
    scoreLabelText.setFillColor(Color::White);
    scoreLabelText.setPosition(width / 2 - scoreLabelText.getGlobalBounds().width / 2, (height / 2 - 70)+20);

  
    scoreValueText.setFont(font);
    scoreValueText.setCharacterSize(56);
    scoreValueText.setFillColor(sf::Color(255, 140, 0));
    setScore(finalScore);
    scoreValueText.setPosition(width / 2 - scoreValueText.getGlobalBounds().width / 2, (height / 2)+20);

    // Menu options
    std::string options[] = { "RETURN TO MAIN MENU", "EXIT" };
    menuOptions.clear();

    for (int i = 0; i < 2; ++i) {
        Text optionText;
        optionText.setFont(font);
        optionText.setString(options[i]);
        optionText.setCharacterSize(26);
        optionText.setFillColor(i == selectedIndex ? sf::Color(255, 215, 0) : sf::Color::White);
        optionText.setPosition(width / 2 - optionText.getGlobalBounds().width / 2,( height / 2 + 100 + i * 55)+30);
        menuOptions.push_back(optionText);
    }
}


void FinalScoreMenu::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    window.draw(titleText);
    window.draw(scoreLabelText);
    window.draw(scoreValueText);
    window.draw(subtitleText);
    for (const auto& option : menuOptions) {
        window.draw(option);
    }
}

void FinalScoreMenu::moveUp() {
    if (selectedIndex > 0) {
        menuOptions[selectedIndex].setFillColor(sf::Color::White);
        selectedIndex--;
        menuOptions[selectedIndex].setFillColor(sf::Color(255, 165, 0));
    }
}

void FinalScoreMenu::moveDown() {
    if (selectedIndex < static_cast<int>(menuOptions.size()) - 1) {
        menuOptions[selectedIndex].setFillColor(sf::Color::White);
        selectedIndex++;
        menuOptions[selectedIndex].setFillColor(sf::Color(255, 165, 0));
    }
}

int FinalScoreMenu::getSelectedIndex() const {
    return selectedIndex;
}

void FinalScoreMenu::setScore(int score) {
    string scoreStr = to_string(score);
    scoreValueText.setString(scoreStr);
    scoreValueText.setPosition(
        titleText.getPosition().x + (titleText.getGlobalBounds().width / 2) - (scoreValueText.getGlobalBounds().width / 2),
        scoreValueText.getPosition().y
    );
}
