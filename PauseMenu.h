#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Menu.h"
#include "Difficulty.h"

class PauseMenu {
public:
	PauseMenu(float width, float height);
	void draw(sf::RenderWindow& window);
	void moveUp();
	void moveDown();
	int getSelectedIndex() const;

private:
	int selectedItemIndex;
	Font font;
	Text menu[2];
	Text title;
	RectangleShape background;
};