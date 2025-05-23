#include "Pacman.h"
#include <cmath>
#include <iostream>
#include "Map.h"
#include "Game.h"

Pacman::Pacman(float startX, float startY, float size)
    : speed(60.0f), direction(0, 0), desiredDirection(0, 0), score(0),
    currentFrame(0), animationTimer(0.0f), animationSpeed(0.1f) {

    if (!texture.loadFromFile("assets/pics/Pacman16.png")) {
        cerr << "Failed to load Pacman sprite sheet." << endl;
    }

    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
    sprite.setOrigin(8, 8);
    sprite.setScale(size / 8.0f, size / 8.0f);
    sprite.setPosition(startX, startY);
}

Vector2f Pacman::getPosition() const {
    return sprite.getPosition();
}

void Pacman::resetPacman(float startX, float startY, float size) {

    direction = Vector2f(0, 0);
    desiredDirection = Vector2f(0, 0);
    // score = 0 ;
    currentFrame = 2;
    animationTimer = 0.0f;
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
    sprite.setOrigin(8, 8);
    sprite.setScale(size / 8.0f, size / 8.0f);
    sprite.setPosition(startX, startY);

}

void Pacman::resetScore() {
    score = 0;
}

void Pacman::setScore(int s) {
    score = s;
}

void Pacman::handleInput() {
    if (Keyboard::isKeyPressed(Keyboard::Up)) {
        desiredDirection = Vector2f(0, -1);
    }
    else if (Keyboard::isKeyPressed(Keyboard::Down)) {
        desiredDirection = Vector2f(0, 1);
    }
    else if (Keyboard::isKeyPressed(Keyboard::Left)) {
        desiredDirection = Vector2f(-1, 0);
    }
    else if (Keyboard::isKeyPressed(Keyboard::Right)) {
        desiredDirection = Vector2f(1, 0);
    }
}

void Pacman::draw(RenderWindow& window) {
    window.draw(sprite);
}

void Pacman::update(Map& map, int tileSize, float deltaTime , bool& eated) {

    Vector2f pos = sprite.getPosition();

    int currentCol = static_cast<int>(pos.x / tileSize);
    int currentRow = static_cast<int>(pos.y / tileSize);

    float centerX = (currentCol + 0.5f) * tileSize;
    float centerY = (currentRow + 0.5f) * tileSize;

    float dx = abs(pos.x - centerX);
    float dy = abs(pos.y - centerY);

    bool isCentered = dx < 2.0f && dy < 2.0f;

    if (isCentered) {
        int desiredCol = currentCol + static_cast<int>(desiredDirection.x);
        int desiredRow = currentRow + static_cast<int>(desiredDirection.y);

        if (!map.isWallAt(desiredCol, desiredRow)) {
            direction = desiredDirection;
            sprite.setPosition(centerX, centerY);
        }
    }

    Vector2f newPos = pos + direction * speed * deltaTime;
    int newCol = static_cast<int>((newPos.x + tileSize / 2 * direction.x) / tileSize);
    int newRow = static_cast<int>((newPos.y + tileSize / 2 * direction.y) / tileSize);

    if (!map.isWallAt(newCol, newRow)) {
        sprite.setPosition(newPos);
    }

    
    if (sprite.getPosition().x < 0) {
        sprite.setPosition(map.getWidth() * tileSize - tileSize / 2, sprite.getPosition().y);
    }
    else if (sprite.getPosition().x >= map.getWidth() * tileSize) {
        sprite.setPosition(tileSize / 2, sprite.getPosition().y);
    }

    // Eating logic
    currentCol = static_cast<int>(sprite.getPosition().x / tileSize);
    currentRow = static_cast<int>(sprite.getPosition().y / tileSize);

    if (map.eatDotAt(currentCol, currentRow, score)) {
        isEating = true;
        eated = true;
        eatingTimer = eatingDuration;
        animationStep = 0;
        animationTimer = 0.0f;
    }

    // Animation control
    if (eatingTimer > 0.0f) {
        eatingTimer -= deltaTime;
        animationTimer += deltaTime;

        if (animationTimer >= animationSpeed && animationStep < eatingSequence.size()) {
            currentFrame = eatingSequence[animationStep];
            animationStep++;
            animationTimer = 0.0f;
        }
    }
    else {
        currentFrame = 2;
    }

    int directionIndex = 0;
    if (direction == Vector2f(1, 0)) directionIndex = 0; // right
    else if (direction == Vector2f(0, -1)) directionIndex = 1; // up
    else if (direction == Vector2f(-1, 0)) directionIndex = 2; // left
    else if (direction == Vector2f(0, 1)) directionIndex = 3; // down

    sprite.setTextureRect(IntRect(currentFrame * 16, directionIndex * 16, 16, 16));
}

int Pacman::getScore() const {
    return score;
}

 void Pacman::setDifficulty(Difficulty diffe) {

    switch (diffe) {
    case Difficulty::Easy:
        speed = 65.0f;
        break;
    case Difficulty::Medium: 
        speed = 80.0f;
        break;
    case Difficulty::Hard:
        speed = 100.0f;
        break;
    }

}

 pair<int, int> Pacman::getTilePos(int tileSize) const {
     Vector2f pos = shape.getPosition();
     return { static_cast<int>(pos.y / tileSize), static_cast<int>(pos.x / tileSize) };
 }


