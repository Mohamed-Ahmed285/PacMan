#include <vector>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
using namespace std;
using namespace sf;
class LoseMenu {
public:
    LoseMenu(float width, float height, int score);
    sf::Font font;
    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int getSelectedIndex() const;
    void setScore(int score);
    void Musicp();
    Music music;
private:
    int selectedIndex;
    vector<sf::Text> menuOptions;
    Text gameOverText;
    Text scoreLabelText; 
    Text scoreValueText; 
    Texture background;
    Sprite backgroundSprite;

};

