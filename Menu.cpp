#include "Menu.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace std;
using namespace sf;

Menu::Menu(float width, float height)
{

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

    // Load image
    if (!title.loadFromFile("assets/pics/title4.png"))
    {
       cerr << "Failed to load image!" << endl;
    }

    // Setup sprite
    sp.setTexture(title);
    float targetWidth = 600.0f;
    float scale = targetWidth / title.getSize().x;
    sp.setScale(scale, scale);

    float x = ((width - (title.getSize().x * scale)) / 2);
    float y = 120.0f;
    sp.setPosition(x + 10 , y);

    if (!pac.loadFromFile("assets/pics/pac.png"))
    {
        cerr << "Failed to load image!" << endl;
    }
    pacsp.setTexture(pac);
    float targetWidth2 = 200.0f;
    float scale2 = targetWidth2 / pac.getSize().x;
    pacsp.setScale(scale2, scale2);

    float x2 = ((width - (pac.getSize().x * scale2)) / 2) + 270;
    float y2 = 270.0f;
    pacsp.setPosition(x2 + 10, y2);

    // Load font
    if (!font.loadFromFile("assets/fonts/Emulogic.otf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
    }

    for (int i = 0; i < MAIN_ITEMS; ++i)
    {
        mainmenu[i].setFont(font);
        mainmenu[i].setString(mainLabels[i]);
        mainmenu[i].setCharacterSize(30);

        FloatRect bounds = mainmenu[i].getLocalBounds();
        mainmenu[i].setOrigin(bounds.width / 2, bounds.height / 2);
        mainmenu[i].setPosition(width / 2.0f, (height / 1.5f +(i * 60.0f))-40);
        mainmenu[i].setFillColor(i == 0 ? Color(255,165,0) : Color::White);
    }

    highscoreText.setFont(font);
    highscoreText.setCharacterSize(24);
    highscoreText.setFillColor(Color(255, 165, 0));
    highscoreText.setPosition(30, 30);
    highscoreText.setString("High Score: " + to_string(highscore));

    if (!music.openFromFile("assets/sounds/background.ogg"))
    {
       cerr << "Failed to load background music!" << std::endl;
    }
    else
    {
        music.setLoop(true);
        music.setVolume(20);
        music.play();
    }

    if (!pacmanTexture.loadFromFile("assets/pics/pacman_small.png"))
    {
        std::cerr << "Failed to load Pac-Man icon!" << std::endl;
    }
    else
    {
        pacmanIcon.setTexture(pacmanTexture);
        pacmanIcon.setScale(0.06f, 0.06f);
    }

    selected = 0;
}

Menu::~Menu() {}

void Menu::setSelected(int n)
{
    selected = n;
}

void Menu::setHighscore(int hs)
{
    highscore = hs;
    highscoreText.setString("High Score: " + to_string(highscore));
}

void Menu::setState(MenuState newState)
{

    state = newState;
    selected = 0;
    const string *labels = (state == MenuState::Main) ? mainLabels : diffLabels;
    int count = (state == MenuState::Main) ? MAIN_ITEMS : DIFF_ITEMS;

    for (int i = 0; i < count; ++i)
    {
        mainmenu[i].setString(labels[i]);
        FloatRect bounds = mainmenu[i].getLocalBounds();
        mainmenu[i].setOrigin(bounds.width / 2, bounds.height / 2);
        mainmenu[i].setPosition(500.0f, 600.0f / 1.5f + i * 50.0f);
        mainmenu[i].setFillColor(i == 0 ? sf::Color{253, 253, 0} : sf::Color::White);
    }
}

void Menu::draw(RenderWindow &window)
{

    Vector2f selectedPos = mainmenu[selected].getPosition();
    window.draw(backgroundSprite);
    window.draw(highscoreText);
    pacmanIcon.setPosition(selectedPos.x - 240, selectedPos.y - 12);
    window.draw(pacmanIcon);
    window.draw(sp);
    // window.draw(pacsp);
    for (int i = 0; i < 3; i++)
    {
        window.draw(mainmenu[i]);
    }
}

void Menu::MoveDown()
{

    int itemCount = (state == MenuState::Main) ? MAIN_ITEMS : DIFF_ITEMS;
    mainmenu[selected].setFillColor(Color::White);
    selected = (selected + 1) % itemCount;
    mainmenu[selected].setFillColor(Color{255, 165,0});
    // mainmenu[selected].setCharacterSize(24);
}

void Menu::MoveUp()
{
    int itemCount = (state == MenuState::Main) ? MAIN_ITEMS : DIFF_ITEMS;
    mainmenu[selected].setFillColor(Color::White);
    selected = (selected - 1 + itemCount) % itemCount;
    mainmenu[selected].setFillColor(Color{ 255, 165,0 });
    // mainmenu[selected].setCharacterSize(24);
}

/*
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


*/

void Menu::MusicStop()
{
    music.stop();
}

void Menu::MusicPlay()
{
    music.setLoop(true);
    music.setVolume(20);
    music.play();
}