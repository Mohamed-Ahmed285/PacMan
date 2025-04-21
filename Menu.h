#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
using namespace sf;
using namespace std;

class Menu {

public:
	Text mainmenu[3];
	Menu(float width, float height);
	void draw(RenderWindow& window);
	void MoveUp();
	void MoveDown();
	void setSelected(int n);
	int pressed() {
		return selected;
	}
	~Menu();
private:
	int selected;
	Font font;
	Texture tex;
	Sprite sp;
	Music music;
	Sprite pacmanIcon;
	Texture pacmanTexture;
	Texture backgroundTexture;
	Sprite backgroundSprite;


};
