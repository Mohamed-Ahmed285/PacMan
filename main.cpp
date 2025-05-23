#include "Game.h"
#include "Pacman.h"
#include "FilesManager.h"
#include "Map.h"
#include <iostream>
#define TILE_SIZE 20

int main() 
{
    // ====files test===(ignore pls <3)
   

    FileManager myfileman;
    int highscore = myfileman.loadHighscore();

    // =============================

    Pacman pacman((14 + 0.5f) * TILE_SIZE, (23 + 0.5f) * TILE_SIZE, TILE_SIZE / 2);
    Game game(pacman,highscore);
    int currentscore =  game.run();
    if (currentscore > highscore)
    {
        myfileman.saveHighscore(currentscore);
    }


    //Map myMap("map1.txt", 20);
    //myMap.buildGraph();
    //myMap.printGraph();
    //myMap.printMapWithStars();
   


    return 0;

}

/*


#include<iostream>
#include "FilesManager.h"
#include "Pacman.h"
#include"Menu.h"
#include"Map.h"
#include<sstream>
#include<fstream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<vector>
#include<iomanip>
#include<random>

using namespace std;
using namespace sf;
enum class GamePage { Menu, Game, Exit };

//int page = 1000;
int main() {



    const int TILE_SIZE = 20;
    GamePage page = GamePage::Menu;
    sf::RenderWindow window(sf::VideoMode(1000, 600), "Pac-Man Game");
    window.setFramerateLimit(60); // Add it here too
    Menu menu(1000, 600);
    Map map("Map.txt", TILE_SIZE);
    Pacman pacman((14 + 0.5f) * TILE_SIZE, (23 + 0.5f) * TILE_SIZE, TILE_SIZE / 2);
    Clock clock;
    int score = 0;
    Font font;
    if (!font.loadFromFile("assets/fonts/Emulogic.otf")) {
        cerr << "Error loading font.\n";
    }

    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(10, 10);
    scoreText.setString("Score: 0");

    while (window.isOpen()) {
        sf::Event event;
        sf::Time deltaTime = clock.restart();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (page == GamePage::Menu) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Up) menu.MoveUp();
                    if (event.key.code == sf::Keyboard::Down) menu.MoveDown();

                    if (event.key.code == sf::Keyboard::Return) {
                        int selected = menu.pressed();
                        if (selected == 0) {
                            window.create(sf::VideoMode(560, 620), "Game View");
                            //window.setFramerateLimit(60); // Add it here too
                            page = GamePage::Game;
                            menu.MusicStop();
                        }
                        else if (selected == 1) page = GamePage::Exit;
                    }
                }
            }
        }

        // Page Switching Logic
        if (page == GamePage::Exit) {
            window.close();
        }

        window.clear();

        if (page == GamePage::Menu) {
            menu.draw(window);

        }

        if (page == GamePage::Game) {

            pacman.handleInput();
            pacman.update(map, TILE_SIZE); // Pass graph to update method

            // Update score text
            scoreText.setString("Score: " + std::to_string(pacman.getScore()));

            // Draw game world
            map.draw(window);
            pacman.draw(window);
            window.draw(scoreText);


        }

        window.display();
    }

    return 0;

}



*/
/* if (page == 1000) {

              while (mywindow.isOpen())
              {
                  Event event;
                  while (mywindow.pollEvent(event))
                  {
                      if (event.type == Event::Closed) {
                          mywindow.close();
                          break;
                      }
                      if (event.type == Event::KeyPressed) {
                          if (event.key.code == Keyboard::Up)
                          {
                              menu.MoveUp();
                          }
                          if (event.key.code == Keyboard::Down)
                          {
                              menu.MoveDown();
                          }
                          if (event.key.code == Keyboard::Return) {
                              if (menu.pressed() == 0)
                              {
                                  page = 0;
                              }
                              if (menu.pressed() == 1)
                              {
                                  page = 1;
                              }
                              if (menu.pressed() == 2)
                              {
                                  page = -1;
                              }
                          }
                      }
                  }

                  mywindow.clear();
                  if (page != 1000)
                  {
                      break;
                  }
                  menu.draw(mywindow);
                  mywindow.display();
              }
              if (page == -1) {
                  mywindow.close();
              }
              if (page == 0) {
                  mywindow.close();

                  sf::RenderWindow window(sf::VideoMode(28 * TILE_SIZE, 31 * TILE_SIZE), "Pac-Man Map");

                  while (window.isOpen()) {
                      sf::Event event;
                      while (window.pollEvent(event)) {
                          if (event.type == sf::Event::Closed)
                              window.close();
                      }

                      window.clear();
                      map.draw(window);
                      window.display();
                  }
              }

          }
    */


   