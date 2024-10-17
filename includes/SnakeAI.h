#ifndef SNAKEAI_H
#define SNAKEAI_H

#include <SFML/System.hpp>
#include <vector>
#include <deque>
#include <utility> // Pour std::pair
#include "Snake.h"
#include "Food.h"
#include <queue>
#include <unordered_set>

// Fonction de hash pour std::pair<int, int>
struct PairHash {
    std::size_t operator()(const std::pair<int, int>& pair) const {
        return std::hash<int>()(pair.first) ^ (std::hash<int>()(pair.second) << 1);
    }
};

// Structure pour représenter une cellule dans la grille
struct Cell {
    int x, y;
    float gCost; // Coût du chemin depuis le départ
    float hCost; // Heuristique (distance estimée jusqu'à la fin)
    float fCost; // gCost + hCost
    Cell* parent;

    Cell(int _x, int _y) : x(_x), y(_y), gCost(0), hCost(0), fCost(0), parent(nullptr) {}
};

// Comparateur pour la priority_queue basée sur fCost
struct CompareCell {
    bool operator()(const Cell* a, const Cell* b) const {
        return a->fCost > b->fCost;
    }
};

class SnakeAI {
public:
    SnakeAI(float windowWidth, float windowHeight, float gridSize);
    sf::Vector2f getNextDirection(const Snake& snake, const std::vector<Food>& foods);
    const std::deque<sf::Vector2f>& getLastPath() const { return lastPath; }

private:
    float windowWidth;
    float windowHeight;
    float gridSize;
    int gridCols;
    int gridRows;
    std::deque<sf::Vector2f> lastPath;

    std::vector<std::vector<bool>> grid; // true si la cellule est occupée

    void initializeGrid(const Snake& snake, const std::vector<Food>& foods);
    std::vector<Cell*> getNeighbors(Cell* current);
    float heuristic(int x1, int y1, int x2, int y2);
    std::deque<sf::Vector2f> findPath(int startX, int startY, int endX, int endY);
    int calculateAccessibleSpace(int x, int y);
    bool isPathSafe(const std::deque<sf::Vector2f>& path, const Snake& snake);
};

#endif // SNAKEAI_H
