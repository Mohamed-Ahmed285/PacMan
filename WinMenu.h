#include <vector>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
using namespace std;
using namespace sf;

class WinMenu {
public:
    WinMenu(float width, float height, int score);
    Font font;
    void draw(RenderWindow& window);
    void moveUp();
    void moveDown();
    int getSelectedIndex() const;
    void setScore(int score);

private:
    int selectedIndex;
    vector<Text> menuOptions;
    Text winnertext;
    Text scoreLabelText; 
    Text scoreValueText;  
    Texture backgroundTexture;
    Sprite backgroundSprite;

};
