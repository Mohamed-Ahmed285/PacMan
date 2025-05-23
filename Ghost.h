#pragma once
#include <SFML/Graphics.hpp>
#include <queue>
#include <map>
#include <cmath>
#include <vector>
#include "Map.h"
#include "Difficulty.h"

using namespace sf;
using namespace std;

class Ghost {
public:
    Ghost(int startCol, int startRow, Difficulty difficulty,const string& texturePath,float size = 10.0f);
    void update(Map& map, const Vector2f& pacmanPos, float deltaTime, int tileSize);
    void draw(RenderWindow& window);
    void setDifficulty(Difficulty difficulty);
    Vector2f getPosition() const;
    pair<int, int> getTilePos(int tileSize) const;
    void reset(int col, int row, int tileSize);

private:
    vector<Vector2f> findPathBFS(Map& map, const Vector2f& start, const Vector2f& target);
    vector<Vector2f> findPathAStar(Map& map, const Vector2f& start, const Vector2f& target);
    float heuristic(const Vector2f& a, const Vector2f& b);
    Vector2f getNextMove(Map& map, const Vector2f& targetPos, int tileSize);
    Sprite sprite;
    Texture texture;
    Vector2f direction;
    Vector2f position;
    float speed;
    Difficulty difficulty;
    Color color;
    //CircleShape shape;
    vector<Vector2f> currentPath;
    int currentPathIndex;
    float scatterTimer;
    float chaseTimer;
    bool isScattering;
};