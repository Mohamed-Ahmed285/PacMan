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

int main() {


    RenderWindow mywindow(VideoMode(1200, 600), "Game");
    Menu menu(1200, 600);
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
            }
        }

        mywindow.clear();
        menu.draw(mywindow);
        mywindow.display();
    }




    /*   ====files test===(ignore pls <3)
    FileManager myfileman;
    int highscore = myfileman.loadHighscore();
    cout <<  highscore;
    myfileman.saveHighscore(highscore);
    */


}
