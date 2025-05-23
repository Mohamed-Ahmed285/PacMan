#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
using namespace std;
using namespace sf;

class FinalScoreMenu {
public:

    FinalScoreMenu(float width, float height, int finalScore);
    void draw(RenderWindow& window);
    void moveUp();
    void moveDown();
    int getSelectedIndex() const;
    void setScore(int score);

private:
    Font font;
    Text titleText;
    Text subtitleText;
    Text scoreLabelText;
    Text scoreValueText;
    vector<Text> menuOptions;
    int selectedIndex;
    Texture background;
    Sprite backgroundSprite;
};
