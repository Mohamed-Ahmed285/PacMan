#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
using namespace sf;
using namespace std;


enum class MenuState {
	Main,
	Difficulty,
};


class Menu {



public:
	void setHighscore(int hs);
	static const int MAIN_ITEMS = 3;
	static const int DIFF_ITEMS = 3;
	MenuState state = MenuState::Main;
	string mainLabels[MAIN_ITEMS] = { "Play", "Instructions", "Exit" };
	string diffLabels[DIFF_ITEMS] = { "Easy", "Medium", "Hard" };
	Text mainmenu[3];
	Menu(float width, float height);
	void draw(RenderWindow& window);
	void MoveUp();
	void MoveDown();
	void setSelected(int n);
	int pressed() {
		return selected;
	}
	void MusicStop();
	void MusicPlay();
	void setState(MenuState newState);
	~Menu();
private:

	Text highscoreText;
	int highscore = 0;
	int selected;
	Font font;
	Texture title;
	Texture pac;
	Sprite sp;
	Sprite pacsp;
	Music music;
	Sprite pacmanIcon;
	Texture pacmanTexture;
	Texture backgroundTexture;
	Sprite backgroundSprite;


};
