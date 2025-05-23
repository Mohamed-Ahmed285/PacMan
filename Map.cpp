#include "Map.h"
#include <fstream>
#include <iostream>

using namespace std;
using namespace sf;

Map::Map(string filename, int tileSize)
    : tileSize(tileSize),
    dot(tileSize / 8.0f),
    pellet(tileSize / 4.0f)
{


    if (!wallTexture.loadFromFile("assets/pics/Map16.png")) {
        cerr << "Failed to load wall texture from Map16.png\n";
    }
    else {
        wallSprite.setTexture(wallTexture);
        wallSprite.setScale(
            static_cast<float>(tileSize) / wallTexture.getSize().x,
            static_cast<float>(tileSize) / wallTexture.getSize().y
        );
    }


    if (!backgroundTexture.loadFromFile("assets/pics/map2.png"))
    {
        cerr << "Failed to load background image from map.png\n";
    }
    else
    {
        backgroundSprite.setTexture(backgroundTexture);
    }

    dot.setFillColor(Color::White);
    pellet.setFillColor(Color::White);
    wall.setFillColor(Color::Blue);
    //wall.setScale(tileSize, tileSize);
    wall.setSize(Vector2f(tileSize,tileSize));
    loadFromFile(filename);

    backgroundSprite.setScale(
        560.0f / backgroundTexture.getSize().x,
        620.0f / backgroundTexture.getSize().y);

    //buildGraph();

};

void Map::UpdateMap(string filename, int tileSize , string background) {
    if (!backgroundTexture.loadFromFile(background))
    {
        cerr << "Failed to load background image from map.png\n";
    }
    else
    {
        backgroundSprite.setTexture(backgroundTexture);
    }

    dot.setFillColor(Color::White);
    pellet.setFillColor(Color::White);

    loadFromFile(filename);

    backgroundSprite.setScale(
        560.0f / backgroundTexture.getSize().x,
        620.0f / backgroundTexture.getSize().y);
}

void Map::loadFromFile(string filename)
{
    ifstream file(filename);
    if (!file)
    {
        cerr << "Failed to open map file: " << filename << "\n";
        return;
    }

    mapData.clear();
    string line;
    while (getline(file, line))
    {
        mapData.push_back(line);
    }

    buildGraph();
}
void Map::buildGraph()
{
    adjacencyList.clear();

    for (int row = 0; row < mapData.size(); row++)
    {
        for (int col = 0; col < mapData[row].size(); col++)
        {
            if (isWallAt(col, row))
                continue;

            pair<int, int> current = { row, col };
            vector<pair<int, int>> neighbors;

            int dRow[] = { -1, 1, 0, 0 };
            int dCol[] = { 0, 0, -1, 1 };

            for (int d = 0; d < 4; ++d)
            {
                int newRow = row + dRow[d];
                int newCol = col + dCol[d];

                if (!isWallAt(newCol, newRow))
                {
                    neighbors.emplace_back(newRow, newCol);
                }
            }

            adjacencyList[current] = neighbors;
        }
    }
}

map<Node, vector<Node>> Map::getGraph()
{
    return adjacencyList;
}

bool Map::isWallAt(int col, int row) const
{
    if (row < 0 || row >= mapData.size() || col < 0 || col >= mapData[row].size())
        return true;

    char tile = mapData[row][col];
    return tile == '|' || tile == '_' || tile == '-';
}

void Map::draw(RenderWindow &window)
{

    for (size_t row = 0; row < mapData.size(); row++)
    {
        for (size_t col = 0; col < mapData[row].size(); col++)
        {
            char tile = mapData[row][col];
            float x = col * tileSize;
            float y = row * tileSize;

            switch (tile)
            {
            case '|':
            case '_':
            case '-':
               //wall.setPosition(x, y);
               //window.draw(wall);
                break;
            case '.':
                dot.setPosition(x + tileSize / 2 - dot.getRadius(), y + tileSize / 2 - dot.getRadius());
                window.draw(dot);
                break;
            case 'o':
                pellet.setPosition(x + tileSize / 2 - pellet.getRadius(), y + tileSize / 2 - pellet.getRadius());
                window.draw(pellet);
                break;
            default:
                break;
            }
        }
    }
    window.draw(backgroundSprite);
}

bool Map::eatDotAt(int col, int row, int &score)
{
    if (row < 0 || row >= mapData.size() || col < 0 || col >= mapData[row].size())
    {
        return false;
    }

    char tile = mapData[row][col];
    if (tile == '.')
    {
        mapData[row][col] = ' ';
        score += 10;
        return true;
    }
    else if (tile == 'o')
    {
        mapData[row][col] = ' ';
        score += 50;
        return true;
    }

    return false;
}

int Map::getWidth() const
{
    return mapData.empty() ? 0 : mapData[0].size();
}

bool Map::hasDotsLeft() {
    for (const auto& row : mapData) {
        for (char tile : row) {
            if (tile == '.' || tile == 'o') {
                return true;
            }
        }
    }
    return false; 
}

/*

void Map::printGraph() {
    for (const auto& entry : adjacencyList) {
        pair<int, int> node = entry.first;
        const vector<pair<int, int>>& neighbors = entry.second;

        cout << "Node (" << node.first << ", " << node.second << "): ";
        for (const auto& neighbor : neighbors) {
            cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
        }
        cout << endl;
    }
}


void Map::printMapWithStars() {
    for (int row = 0; row < mapData.size(); ++row) {
        for (int col = 0; col < mapData[row].size(); ++col) {
            pair<int, int> pos = { row, col };
            if (adjacencyList.find(pos) != adjacencyList.end()) {
                cout << '*'; 
            }
            else {
                cout << mapData[row][col];
            }
        }
        cout << endl;
    }
}

*/