#include<iostream>
#include "FilesManager.h"
#include<sstream>
#include<fstream>
#include<SFML/Graphics.hpp>
using namespace std;
using namespace sf;

int main() {


	RenderWindow window(VideoMode(1280, 720), "Sfml sucks");
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
    }
    window.clear();
    window.display();
    /*
    FileManager myfileman;
    int highscore = myfileman.loadHighscore();
    cout <<  highscore;
    myfileman.saveHighscore(highscore);
    */


}
