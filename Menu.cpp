#include "Menu.h"
#include <iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
using namespace std;
using namespace sf;


Menu::Menu(float width, float height) {

    // Load title image
    if (!tex.loadFromFile("assets/pics/title.png")) {
        std::cerr << "Failed to load image!" << std::endl;
    }

    // Load font 
    if (!font.loadFromFile("assets/fonts/Emulogic.otf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }

    // Setup sprite
    sp.setTexture(tex);
    float targetWidth = 600.0f; // desired width for the image
    float scale = targetWidth / tex.getSize().x;
    sp.setScale(scale, scale);

    // Center sprite horizontally, place it near the top
    float x = (width - (tex.getSize().x * scale)) / 2;
    float y = 20.0f;
    sp.setPosition(x + 10, y);

    // Setup menu items
    const std::string labels[3] = { "Play", "Instructions", "Exit" };
    for (int i = 0; i < 3; ++i) {
        mainmenu[i].setFont(font);
        mainmenu[i].setString(labels[i]);
        mainmenu[i].setCharacterSize(20);

        // Center each item horizontally using origin + position
        sf::FloatRect bounds = mainmenu[i].getLocalBounds();
        mainmenu[i].setOrigin(bounds.width / 2, bounds.height / 2);
        mainmenu[i].setPosition(width / 2.0f, height / 1.5f + i * 50.0f);

        // Color: yellow for selected, white otherwise
        mainmenu[i].setFillColor(i == 0 ? sf::Color{ 253, 253, 0 } : sf::Color::White);
    }

    if (!music.openFromFile("assets/sounds/background.ogg")) {
        std::cerr << "Failed to load background music!" << std::endl;
    }
    else {
        music.setLoop(true);
        music.setVolume(50);
        music.play();
    }

    if (!pacmanTexture.loadFromFile("assets/pics/pacman_small.png")) {
        std::cerr << "Failed to load Pac-Man icon!" << std::endl;
    }
    else {
        pacmanIcon.setTexture(pacmanTexture);
        pacmanIcon.setScale(0.05f, 0.05f); // scale if it's too big
    }

    selected = 0;
}


Menu::~Menu() {}


void Menu::setSelected(int n) {
    selected = n;
}


void Menu::draw(RenderWindow& window) {
    // Get the position of the selected menu item
    Vector2f selectedPos = mainmenu[selected].getPosition();

    // Place Pac-Man slightly to the left of the text
    pacmanIcon.setPosition(selectedPos.x - 180, selectedPos.y - 12); // Adjust offsets as needed
    window.draw(pacmanIcon);
    window.draw(sp);
    for (int i = 0; i < 3; i++)
    {
        window.draw(mainmenu[i]);
    }
}

void Menu::MoveDown() {
    if (selected + 1 <= 3)
    {
        mainmenu[selected].setFillColor(Color::White);
        selected++;
        if (selected == 3)
        {
            selected = 0;
        }
        mainmenu[selected].setFillColor(Color{ 253,253,0 });
    }
}

void Menu::MoveUp() {
    if (selected - 1 >= -1)
    {
        mainmenu[selected].setFillColor(Color::White);
        selected--;
        if (selected == -1) {
            selected = 2;
        }
        mainmenu[selected].setFillColor(Color{ 253,253,0 });

    }
}