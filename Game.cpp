#include "Game.h"
#include "Pacman.h"
#include "Ghost.h"
#include "PauseMenu.h"
#include <iostream>
#include <thread>

Game::Game(Pacman &pacman, int highscore)
    : window(sf::VideoMode(1000, 600), "Pac-Man Game"),
      menu(1000, 600),
      map("Map1.txt", TILE_SIZE),
      pacman(pacman),
      pauseMenu(560, 620),
      finalScoreMenu(1000, 600, 0),
      losemenu(1000, 600, 0),
      winmenu(1000, 600, 0),
      score(0), page(Page::Menu),
      instructionsPage(font, window.getSize()), highscore(highscore)
{
    menu.setHighscore(highscore);

    if (!font.loadFromFile("assets/fonts/Emulogic.otf"))
    {
        cerr << "Error loading font.\n";
    }

    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(10, 10);
    scoreText.setString("Score: 0");

    // Ghost initialization (position, color)
    ghosts.push_back(make_unique<Ghost>(13.5f, 13.0f, Difficulty::Medium, "assets/pics/ghost1.png"));
    ghosts.push_back(make_unique<Ghost>(12.5f, 13.0f, Difficulty::Medium, "assets/pics/ghost2.png"));
    ghosts.push_back(make_unique<Ghost>(14.5f, 13.0f, Difficulty::Medium, "assets/pics/ghost3.png"));
    ghosts.push_back(make_unique<Ghost>(13.5f, 14.0f, Difficulty::Medium, "assets/pics/ghost4.png"));

    if (!coin.openFromFile("assets/sounds/coin.ogg"))
    {
        cout << "Failed to load coin sound!" << endl;
    }
    else
    {
        coin.setVolume(10);
    }
}

int Game::run()
{
    while (window.isOpen())
    {
        Time deltaTime = clock.restart();
        processEvents();
        update(deltaTime);
        render();
    }
    return highscore;
}

void Game::processEvents()
{
    sf::Event event;

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (page == Page::Menu)
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    menu.MoveUp();
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    menu.MoveDown();
                }
                else if (event.key.code == sf::Keyboard::Return)
                {

                    if (menu.state == MenuState::Main)
                    {
                        if (menu.pressed() == 0)
                        {
                            menu.setState(MenuState::Difficulty);
                        }
                        else if (menu.pressed() == 1)
                        {

                            page = Page::Instructions;
                            instructionsPage.setActive(true);
                            // menu.MusicStop();
                        }
                        else if (menu.pressed() == 2)
                        {
                            page = Page::Exit;
                        }
                    }
                    else if (menu.state == MenuState::Difficulty)
                    {

                        Difficulty diff = static_cast<Difficulty>(menu.pressed());

                        window.clear();
                        window.create(VideoMode(560, 620), "Pac-Man Game");
                        map.UpdateMap("Map1.txt", TILE_SIZE, "assets/pics/map1.png");
                        pacman.resetPacman((14 + 0.5f) * TILE_SIZE, (23 + 0.5f) * TILE_SIZE, TILE_SIZE / 2);
                        resetGhosts();
                        window.setFramerateLimit(60);
                        page = Page::Game;
                        pacman.setDifficulty(diff);
                        for (auto &ghost : ghosts)
                        {
                            ghost->setDifficulty(diff);
                        }
                        menu.MusicStop();
                    }
                }
            }
        }

        else if (page == Page::Instructions && event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Return)
            {
                page = Page::Menu;
            }
        }

        else if (page == Page::Game)
        {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                page = Page::Pause;
                menu.MusicPlay();
            }
            else if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W)) {

                if (currentMap == 1)
                {
                    window.clear();
                    window.create(sf::VideoMode(1000, 600), "Pac-Man Game");
                    page = Page::Win;
                    menu.MusicPlay();
                    winmenu.setScore(pacman.getScore());
                }
                else if (currentMap == 2)
                {
                    window.clear();
                    menu.MusicPlay();
                    window.create(sf::VideoMode(1000, 600), "Pac-Man Game");
                    page = Page::FinalScore;
                    finalScoreMenu.setScore(pacman.getScore());
                }
            }
     
        }

        else if (page == Page::Pause)
        {
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Up)
                    pauseMenu.moveUp();
                else if (event.key.code == Keyboard::Down)
                    pauseMenu.moveDown();
                else if (event.key.code == Keyboard::Return)
                {
                    int selected = pauseMenu.getSelectedIndex();
                    if (selected == 0)
                    {
                        // Resume
                        menu.MusicStop();
                        page = Page::Game;
                    }
                    else if (selected == 1)
                    {
                        window.clear();
                        window.create(sf::VideoMode(1000, 600), "Pac-Man Game");
                        window.setFramerateLimit(60);
                        pacman.resetScore();
                        scoreText.setString("Score: " + std::to_string(pacman.getScore()));
                        page = Page::Menu;
                        menu.setState(MenuState::Main);
                        menu.MusicPlay();
                        // Return to main menu
                    }
                }
            }
        }

        else if (page == Page::Win)
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    winmenu.moveUp();
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    winmenu.moveDown();
                }
                else if (event.key.code == sf::Keyboard::Return)
                {
                    int selected = winmenu.getSelectedIndex();
                    if (selected == 0)
                    {
                        window.clear();
                        menu.MusicStop();
                        window.create(VideoMode(560, 620), "Pac-Man Game");
                        currentMap = 2;
                        map.UpdateMap("Map2.txt", TILE_SIZE, "assets/pics/map2.png");
                        pacman.resetPacman((13.5f) * TILE_SIZE, (24.5f) * TILE_SIZE, TILE_SIZE / 2);
                        resetGhosts();
                        score = pacman.getScore();
                        page = Page::Game;
                    }
                    else if (selected == 1)
                    {

                        window.clear();
                        window.create(VideoMode(1000, 600), "Pac-Man Game");
                        page = Page::Menu;
                        currentMap = 1;
                        if (pacman.getScore() > highscore)
                        {
                            highscore = pacman.getScore();
                            menu.setHighscore(highscore);
                        }
                        pacman.resetScore();
                        menu.setState(MenuState::Main);
                        menu.MusicPlay();
                    }
                }
            }
        }

        else if (page == Page::Lose)
        {

            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Up)
                {
                    losemenu.moveUp();
                }
                else if (event.key.code == Keyboard::Down)
                {
                    losemenu.moveDown();
                }
                else if (event.key.code == Keyboard::Return)
                {
                    int selected = losemenu.getSelectedIndex();
                    if (selected == 0)
                    {
                        window.clear();
                        window.create(VideoMode(560, 620), "Pac-Man Game");
                        if (currentMap == 1)
                        {
                            map.UpdateMap("Map1.txt", TILE_SIZE, "assets/pics/map1.png");
                            pacman.resetPacman((14 + 0.5f) * TILE_SIZE, (23 + 0.5f) * TILE_SIZE, TILE_SIZE / 2);
                            resetGhosts();
                            pacman.resetScore();
                            scoreText.setString("Score: " + std::to_string(pacman.getScore()));
                            menu.MusicStop();
                            page = Page::Game;
                        }
                        else if (currentMap == 2)
                        {

                            map.UpdateMap("Map2.txt", TILE_SIZE, "assets/pics/map2.png");
                            pacman.resetPacman((13.5f) * TILE_SIZE, (24.5f) * TILE_SIZE, TILE_SIZE / 2);
                            resetGhosts();
                            pacman.setScore(score);
                            scoreText.setString("Score: " + std::to_string(pacman.getScore()));
                            menu.MusicStop();
                            page = Page::Game;
                        }
                    }
                    else if (selected == 1)
                    {

                        window.clear();
                        window.create(VideoMode(1000, 600), "Pac-Man Game");
                        page = Page::Menu;
                        currentMap = 1;
                        if (pacman.getScore() > highscore)
                        {
                            highscore = pacman.getScore();
                            menu.setHighscore(highscore);
                        }
                        pacman.resetScore();
                        menu.setState(MenuState::Main);
                        menu.MusicPlay();
                    }
                }
            }
        }

        else if (page == Page::FinalScore)
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up)
                    finalScoreMenu.moveUp();
                else if (event.key.code == sf::Keyboard::Down)
                    finalScoreMenu.moveDown();
                else if (event.key.code == sf::Keyboard::Return)
                {
                    int selected = finalScoreMenu.getSelectedIndex();
                    if (selected == 0)
                    {
                        menu.MusicPlay();
                        page = Page::Menu;
                        menu.setState(MenuState::Main);

                        if (pacman.getScore() > highscore)
                        {
                            highscore = pacman.getScore();
                            menu.setHighscore(highscore);
                        }
                        pacman.resetScore();
                        currentMap = 1;
                    }
                    else if (selected == 1)
                    {
                        window.close();
                    }
                }
            }
        }
        }

    if (page == Page::Exit)
    {
        window.close();
    }
}

void Game::update(Time deltaTime)
{
    if (page == Page::Game)
    {
        pacman.handleInput();
        bool eated = false;

        pacman.update(map, TILE_SIZE, deltaTime.asSeconds(), eated);
        if (eated)
        {
            scoreText.setString("Score: " + std::to_string(pacman.getScore()));
            coin.stop();
            coin.play();
        }

        for (auto &ghost : ghosts)
        {
            ghost->update(map, pacman.getPosition(), deltaTime.asSeconds(), TILE_SIZE);

            // Check for collision with pacman
            Vector2f ghostPos = ghost->getPosition();
            Vector2f pacmanPos = pacman.getPosition();
            float distance = sqrt(pow(ghostPos.x - pacmanPos.x, 2) + pow(ghostPos.y - pacmanPos.y, 2));

            if (distance < TILE_SIZE / 2)
            {
                // Handle pacman death
                losemenu.Musicp();
                while (losemenu.music.getStatus() == sf::SoundSource::Playing) {
                    this_thread::sleep_for(std::chrono::milliseconds(100));
                }
                window.clear();
                window.create(sf::VideoMode(1000, 600), "Pac-Man Game");
                losemenu.setScore(pacman.getScore());
                menu.MusicPlay();
                page = Page::Lose;
                break;
            }
        }
        // update for ghosts should be here when i finish

        if (!map.hasDotsLeft())
        {
            if (currentMap == 1)
            {
                window.clear();
                window.create(sf::VideoMode(1000, 600), "Pac-Man Game");
                page = Page::Win;
                menu.MusicPlay();
                winmenu.setScore(pacman.getScore());
            }
            else if (currentMap == 2)
            {
                window.clear();
                menu.MusicPlay();
                window.create(sf::VideoMode(1000, 600), "Pac-Man Game");
                page = Page::FinalScore;
                finalScoreMenu.setScore(pacman.getScore());
            }
        }
       
    }
}

void Game::render()
{
    window.clear();

    if (page == Page::Menu)
    {
        menu.draw(window);
    }
    else if (page == Page::Game)
    {

        map.draw(window);
        pacman.draw(window);

        // Draw ghosts
        for (auto &ghost : ghosts)
        {
            ghost->draw(window);
        }

        window.draw(scoreText);
    }
    else if (page == Page::Instructions)
    {
        instructionsPage.render(window);
    }
    else if (page == Page::Pause)
    {

        map.draw(window);
        pacman.draw(window);
        for (auto &ghost : ghosts)
        {
            ghost->draw(window);
        }
        window.draw(scoreText);
        pauseMenu.draw(window);
    }
    else if (page == Page::Win)
    {
        winmenu.draw(window);
    }
    else if (page == Page::FinalScore)
    {
        finalScoreMenu.draw(window);
    }
    else if (page == Page::Lose)
    {
        losemenu.draw(window);
    }

    window.display();
}

void Game::resetGhosts()
{

    ghosts.at(0)->reset(13.5, 13, 20);
    ghosts.at(1)->reset(12.5, 13, 20);
    ghosts.at(2)->reset(14.5, 13, 20);
    ghosts.at(3)->reset(13.5, 14, 20);
}