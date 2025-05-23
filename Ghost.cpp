#include "Ghost.h"
#include <algorithm>
#include <map>
#include <iostream>
using Node = pair<int, int>;

/*Ghost::Ghost(int startCol, int startRow, Difficulty difficulty, Color color, float size)
    : difficulty(difficulty), color(color), currentPathIndex(0),
    scatterTimer(0.0f), chaseTimer(0.0f), isScattering(false) {

    // Set initial position
    position.x = (startCol + 0.5f) * 20;
    position.y = (startRow + 0.5f) * 20;

   
    setDifficulty(difficulty);
    shape.setRadius(size);
    shape.setFillColor(color);
    shape.setOrigin(size, size);
    shape.setPosition(position);
}*/

Ghost::Ghost(int startCol, int startRow, Difficulty difficulty, const string& texturePath, float size)
    : difficulty(difficulty), currentPathIndex(0),
    scatterTimer(0.0f), chaseTimer(0.0f), isScattering(false)
{
    // Load texture from file
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Failed to load texture from " << texturePath << std::endl;
        // You might want to handle this more gracefully (fallback texture etc)
    }

    // Set sprite texture
    sprite.setTexture(texture);


    float scale = (size * 2) / texture.getSize().x; // scale to diameter
    sprite.setScale(scale *1.3, scale*1.3);

    // Set initial position centered on tile
    position.x = (startCol + 0.5f) * 20;
    position.y = (startRow + 0.5f) * 20;

    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    sprite.setPosition(position.x, position.y);
    setDifficulty(difficulty);
}

void Ghost::update(Map& map, const Vector2f& pacmanPos, float deltaTime, int tileSize) {
 
    scatterTimer += deltaTime;
    chaseTimer += deltaTime;

    Vector2f targetPos = pacmanPos;

  
    if (currentPath.empty() || currentPathIndex >= currentPath.size()) {
        if (difficulty == Difficulty::Easy) {
            currentPath = findPathBFS(map, position, targetPos);
        }
        else {
            currentPath = findPathAStar(map, position, targetPos);
        }
        currentPathIndex = 0;
    }


    if (!currentPath.empty() && currentPathIndex < currentPath.size()) {
        Vector2f target = currentPath[currentPathIndex];
        Vector2f direction = target - position;
        float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

        if (distance < 5.0f) { 
            currentPathIndex++;
        }
        else {
            if (distance > 0) {
                direction /= distance;
                position += direction * speed * deltaTime;
                sprite.setPosition(position);
            }
        }
    }
}

void Ghost::draw(RenderWindow& window) {
    window.draw(sprite);
}

void Ghost::setDifficulty(Difficulty diff) {
    difficulty = diff;
    switch (difficulty) {
    case Difficulty::Easy:
        speed = 50.0f;
        break;
    case Difficulty::Medium:
        speed = 65.0f;
        break;
    case Difficulty::Hard:
        speed = 80.0f;
        break;
    }
}

Vector2f Ghost::getPosition() const {
    return position;
}

pair<int, int> Ghost::getTilePos(int tileSize) const {
    return { static_cast<int>(position.y / tileSize), static_cast<int>(position.x / tileSize) };
}

void Ghost::reset(int col, int row, int tileSize) {
    position.x = (col + 0.5f) * tileSize;
    position.y = (row + 0.5f) * tileSize;
    sprite.setPosition(position);
    currentPath.clear();
    currentPathIndex = 0;
}

vector<Vector2f> Ghost::findPathBFS(Map& MAP, const Vector2f& start, const Vector2f& target) {
    int tileSize = 20; 

    pair<int, int> startNode = {
        static_cast<int>(start.y / tileSize),
        static_cast<int>(start.x / tileSize)
    };

    pair<int, int> targetNode = {
        static_cast<int>(target.y / tileSize),
        static_cast<int>(target.x / tileSize)
    };

    map<Node, vector<Node>> graph = MAP.getGraph();
    queue<Node> q;
    map<Node, bool> visited;
    map<Node, Node> parent;

    q.push(startNode);
    visited[startNode] = true;

    while (!q.empty()) {
        Node current = q.front();
        q.pop();

        if (current == targetNode) {
           
            vector<Vector2f> path;
            Node node = targetNode;

            while (node != startNode) {
                path.push_back(Vector2f(
                    (node.second + 0.5f) * tileSize,
                    (node.first + 0.5f) * tileSize
                ));
                node = parent[node];
            }

            reverse(path.begin(), path.end());
            return path;
        }

        for (Node neighbor : graph[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                parent[neighbor] = current;
                q.push(neighbor);
            }
        }
    }

    return {};
}

vector<Vector2f> Ghost::findPathAStar(Map& gameMap, const sf::Vector2f& start, const sf::Vector2f& target) {
    int tileSize = 20;

    Node startNode = { static_cast<int>(start.y / tileSize), static_cast<int>(start.x / tileSize) };
    Node targetNode = { static_cast<int>(target.y / tileSize), static_cast<int>(target.x / tileSize) };

    map<Node, std::vector<Node>> graph = gameMap.getGraph();
    //cout << "Graph size: " << graph.size() << endl;
    vector<pair<float, Node>> openSet;
    map<Node, float> gScore;
    map<Node, float> fScore;
    map<Node, Node> cameFrom;

     for (const auto& entry : graph) {

        gScore[entry.first] = INFINITY;
        fScore[entry.first] = INFINITY;
     
     }

    gScore[startNode] = 0.0f;
    fScore[startNode] = heuristic(start, target);
    openSet.push_back({ fScore[startNode], startNode });
    make_heap(openSet.begin(), openSet.end(), std::greater<>());

    while (!openSet.empty()) {
        std::pop_heap(openSet.begin(), openSet.end(), std::greater<>());
        Node current = openSet.back().second;
        openSet.pop_back();

        if (current == targetNode) {
           
            vector<Vector2f> path;
            Node node = targetNode;

            while (node != startNode) {
                path.emplace_back(
                    (node.second + 0.5f) * tileSize,
                    (node.first + 0.5f) * tileSize
                );
                node = cameFrom[node];
            }

            reverse(path.begin(), path.end());
            return path;
        }

        for (const Node& neighbor : graph[current]) {
            float tentativeGScore = gScore[current] + 1.0f; // assuming uniform cost

            if (tentativeGScore < gScore[neighbor]) {
                cameFrom[neighbor] = current;
                gScore[neighbor] = tentativeGScore;
                fScore[neighbor] = tentativeGScore + heuristic(
                    Vector2f((neighbor.second + 0.5f) * tileSize, (neighbor.first + 0.5f) * tileSize),
                    target
                );

                // Check if neighbor is in openSet
                auto it = std::find_if(openSet.begin(), openSet.end(),
                    [&](const std::pair<float, Node>& p) { return p.second == neighbor; });
                if (it == openSet.end()) {
                    openSet.push_back({ fScore[neighbor], neighbor });
                    push_heap(openSet.begin(), openSet.end(), std::greater<>());
                }
            }
        }
    }

    return {}; // no path found
}


float Ghost::heuristic(const Vector2f& a, const Vector2f& b) {
    // Manhattan distance
    return abs(a.x - b.x) + abs(a.y - b.y);
}