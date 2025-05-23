#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Menu.h"
#include "Difficulty.h"
using namespace std;
using namespace sf;

class Pacman {
public:
    Pacman(float startX, float startY, float size);
    void handleInput();
    void resetScore();
    void update(Map& map, int tileSize, float deltaTime, bool& eated);
    void draw(sf::RenderWindow& window);
    void setDifficulty(Difficulty diffe);
    Vector2f getPosition() const;
    int getScore() const;
    void setScore(int s);
    pair<int, int> getTilePos(int tileSize) const;
    void resetPacman(float startX, float startY, float size);

private:

    const std::vector<int> eatingSequence = { 2, 3, 4, 5, 0, 1, 2 };
    int animationStep = 0;
    bool isEating = false;
    float eatingTimer = 0.0f;
    float animationTimer = 0.0f;

    float animationSpeed = 0.8f;        
    float eatingDuration = 5.6f;      

    int idleFrame = 2; 

    int currentFrame = idleFrame;
    


    CircleShape shape;
    Vector2f direction;
    Vector2f desiredDirection;
    float speed;
    int score;
    Texture texture;
    Sprite sprite;

};



