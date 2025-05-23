#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <map>
using namespace std;
using namespace sf;
using Node = pair<int, int>;

class Map {
public:
    bool hasDotsLeft();
    void UpdateMap(string filename, int tileSize, string background);
    Map(string filename, int tileSize);
    void draw(RenderWindow& window);
    bool isWallAt(int col, int row) const;
    bool eatDotAt(int col, int row, int& score);
    int getWidth() const;
    //void printGraph();
    //void printMapWithStars();
    map< Node, vector<Node>> getGraph();
    void buildGraph();

private:

    int tileSize;
    RectangleShape wall;
    Texture wallTexture;
    Sprite wallSprite;
    vector<string> mapData;
    map<Node, vector<Node>> adjacencyList;
    void loadFromFile(string filename);
    CircleShape dot;
    CircleShape pellet;
    Texture backgroundTexture;
    Sprite backgroundSprite;

};


   


    

