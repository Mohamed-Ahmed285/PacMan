#include<iostream>
#include "FilesManager.h"
#include"Menu.h"
#include<sstream>
#include<fstream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<vector>
#include<iomanip>
#include<random>

using namespace std;
using namespace sf;
int page = 1000;
int main() {


    RenderWindow mywindow(VideoMode(1200, 600), "Game");
    Menu menu(1200, 600);
    /*Texture mainmenubg;
    mainmenubg.loadFromFile("assets/pics/bg.jpg");
    Sprite bg;
    bg.setTexture(mainmenubg);*/


   
   
        if (page == 1000) {

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
                //PName()
            }
        }



    

   

    /*   ====files test===(ignore pls <3)
    FileManager myfileman;
    int highscore = myfileman.loadHighscore();
    cout <<  highscore;
    myfileman.saveHighscore(highscore);
    */


}
