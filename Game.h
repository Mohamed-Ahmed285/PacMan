#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Map.h"
#include "PauseMenu.h"
#include "Pacman.h"
#include "InstructionsPage.h"
#include "Difficulty.h"
#include "Ghost.h"
#include "WinMenu.h"
#include "LoseMenu.h"
#include "FinalScoreMenu.h"
#include <vector>



class Game {
public:
    Game(Pacman& pacman, int highscore);
    int run();

private:
    void resetGhosts();
    vector<std::unique_ptr<Ghost>> ghosts;
    int currentMap = 1;
    FinalScoreMenu finalScoreMenu;
    PauseMenu pauseMenu;
    LoseMenu losemenu;
    WinMenu winmenu;
    bool isPaused;
    Pacman& pacman; 
    int highscore;
    void processEvents();
    void update(Time deltaTime);
    void render();
    enum class Page { Menu, Game, Instructions , Pause , Win , Lose , FinalScore ,Exit };
    Page page;
    RenderWindow window;
    const int TILE_SIZE = 20;
    Menu menu;
    Map map;
    InstructionsPage instructionsPage;
    Font font;
    Text scoreText;
    int score;
    Clock clock;
    Music coin;

};
