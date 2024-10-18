#include "SnakeAI.h"
#include <algorithm>
#include <cmath>
#include <queue>
#include <unordered_set>
#include <utility>
#include <iostream>

// Implémentation des méthodes de SnakeAI

SnakeAI::SnakeAI(float windowWidth, float windowHeight, float gridSize)
    : windowWidth(windowWidth), windowHeight(windowHeight), gridSize(gridSize)
{
    gridCols = static_cast<int>(windowWidth / gridSize);
    gridRows = static_cast<int>(windowHeight / gridSize);
    grid.resize(gridCols, std::vector<bool>(gridRows, false));
}

void SnakeAI::initializeGrid(const Snake& snake, const std::vector<Food>& foods) {
    // Réinitialiser la grille
    for (int x = 0; x < gridCols; ++x) {
        for (int y = 0; y < gridRows; ++y) {
            grid[x][y] = false;
        }
    }

    // Marquer les cellules occupées par le serpent
    for (const auto& segment : snake.getSegments()) {
        int gridX = static_cast<int>(segment.x / gridSize);
        int gridY = static_cast<int>(segment.y / gridSize);
        if (gridX >= 0 && gridX < gridCols && gridY >= 0 && gridY < gridRows) {
            grid[gridX][gridY] = true;
        }
    }

    // Marquer les cellules occupées par la nourriture
    for (const auto& food : foods) {
        int foodX = static_cast<int>(food.getPosition().x / gridSize);
        int foodY = static_cast<int>(food.getPosition().y / gridSize);
        if (foodX >= 0 && foodX < gridCols && foodY >= 0 && foodY < gridRows) {
            grid[foodX][foodY] = false; // La nourriture ne bloque pas le chemin
        }
    }

    // Les murs sont déjà considérés comme hors grille, donc pas besoin de les marquer
}

std::vector<Cell*> SnakeAI::getNeighbors(Cell* current) {
    std::vector<Cell*> neighbors;
    std::vector<std::pair<int, int>> directions = {
        {0, -1}, // Haut
        {0, 1},  // Bas
        {-1, 0}, // Gauche
        {1, 0}   // Droite
    };

    for (const auto& dir : directions) {
        int newX = current->x + dir.first;
        int newY = current->y + dir.second;

        if (newX >= 0 && newX < gridCols && newY >= 0 && newY < gridRows) {
            if (!grid[newX][newY]) { // Cellule libre
                neighbors.push_back(new Cell(newX, newY));
            }
        }
    }

    return neighbors;
}

float SnakeAI::heuristic(int x1, int y1, int x2, int y2) {
    // Distance de Manhattan
    return static_cast<float>(abs(x1 - x2) + abs(y1 - y2));
}

int SnakeAI::calculateAccessibleSpace(int startX, int startY) {
    // Algorithme de Flood Fill pour compter les cellules accessibles
    std::queue<std::pair<int, int>> q;
    std::vector<std::vector<bool>> visited(gridCols, std::vector<bool>(gridRows, false));
    int accessible = 0;

    q.push({startX, startY});
    visited[startX][startY] = true;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        accessible++;

        std::vector<std::pair<int, int>> directions = {
            {0, -1}, {0, 1}, {-1, 0}, {1, 0}
        };

        for (const auto& dir : directions) {
            int newX = x + dir.first;
            int newY = y + dir.second;

            if (newX >= 0 && newX < gridCols && newY >= 0 && newY < gridRows &&
                !grid[newX][newY] && !visited[newX][newY]) {
                q.push({newX, newY});
                visited[newX][newY] = true;
            }
        }
    }

    return accessible;
}

bool SnakeAI::isPathSafe(const std::deque<sf::Vector2f>& path, const Snake& snake) {
    if (path.empty()) return false;

    // Simuler le serpent après avoir suivi le chemin
    // Copier la grille
    std::vector<std::vector<bool>> tempGrid = grid;

    // Copier les segments du serpent
    std::deque<sf::Vector2f> simulatedSegments = snake.getSegments();
    // Simuler le mouvement
    for (size_t i = 1; i < path.size(); ++i) {
        // Ajouter la nouvelle tête
        simulatedSegments.push_front(path[i]);

        // Supprimer la queue (suppose que le serpent ne mange pas en chemin)
        simulatedSegments.pop_back();

        // Mettre à jour la grille temporaire
        int headX = static_cast<int>(path[i].x / gridSize);
        int headY = static_cast<int>(path[i].y / gridSize);
        tempGrid[headX][headY] = true;
    }

    // Position actuelle de la tête après avoir suivi le chemin
    sf::Vector2f newHead = simulatedSegments.front();
    int newHeadX = static_cast<int>(newHead.x / gridSize);
    int newHeadY = static_cast<int>(newHead.y / gridSize);

    // Calculer l'espace accessible depuis la nouvelle position de la tête
    // Temporarily set the grid to the simulated grid
    std::vector<std::vector<bool>> originalGrid = grid;
    grid = tempGrid;
    int accessibleSpace = calculateAccessibleSpace(newHeadX, newHeadY);
    grid = originalGrid; // Restaurer la grille originale

    // Si l'espace accessible est supérieur ou égal à la longueur du serpent, le chemin est sûr
    return accessibleSpace >= snake.getLength();
}

std::deque<sf::Vector2f> SnakeAI::findPath(int startX, int startY, int endX, int endY) {
    std::deque<sf::Vector2f> path;

    // Liste ouverte (priority_queue basée sur fCost)
    std::priority_queue<Cell*, std::vector<Cell*>, CompareCell> openList;
    // Liste fermée (cellules déjà évaluées)
    std::unordered_set<std::pair<int, int>, PairHash> closedList;

    // Créer la cellule de départ
    Cell* startCell = new Cell(startX, startY);
    startCell->gCost = 0;
    startCell->hCost = heuristic(startX, startY, endX, endY);
    startCell->fCost = startCell->gCost + startCell->hCost;
    openList.push(startCell);

    Cell* endCell = nullptr;

    while (!openList.empty()) {
        Cell* current = openList.top();
        openList.pop();

        // Vérifier si la cellule actuelle est la cellule d'arrivée
        if (current->x == endX && current->y == endY) {
            endCell = current;
            break;
        }

        // Ajouter la cellule actuelle à la liste fermée
        closedList.emplace(std::make_pair(current->x, current->y));

        // Obtenir les voisins de la cellule actuelle
        std::vector<Cell*> neighbors = getNeighbors(current);
        for (auto neighbor : neighbors) {
            // Si le voisin est déjà dans la liste fermée, l'ignorer
            if (closedList.find(std::make_pair(neighbor->x, neighbor->y)) != closedList.end()) {
                delete neighbor;
                continue;
            }

            float tentativeG = current->gCost + 1.0f; // Coût du chemin

            // Chercher si le voisin est déjà dans l'openList
            bool inOpenList = false;
            std::priority_queue<Cell*, std::vector<Cell*>, CompareCell> tempQueue = openList;
            while (!tempQueue.empty()) {
                Cell* cell = tempQueue.top();
                tempQueue.pop();
                if (cell->x == neighbor->x && cell->y == neighbor->y) {
                    inOpenList = true;
                    if (tentativeG < cell->gCost) {
                        cell->gCost = tentativeG;
                        cell->fCost = cell->gCost + cell->hCost;
                        cell->parent = current;
                    }
                    break;
                }
            }

            if (!inOpenList) {
                neighbor->gCost = tentativeG;
                neighbor->hCost = heuristic(neighbor->x, neighbor->y, endX, endY);
                neighbor->fCost = neighbor->gCost + neighbor->hCost;
                neighbor->parent = current;
                openList.push(neighbor);
            } else {
                delete neighbor;
            }
        }

        // Nettoyer les voisins créés
        for (auto neighbor : neighbors) {
            // Les voisins déjà dans openList sont gérés, sinon ils sont déjà supprimés
            // Pas besoin de supprimer ici
        }
    }

    // Si un chemin a été trouvé, reconstruire le chemin
    if (endCell != nullptr) {
        Cell* current = endCell;
        while (current != nullptr) {
            path.emplace_front(static_cast<float>(current->x * gridSize),
                               static_cast<float>(current->y * gridSize));
            current = current->parent;
        }
    }

    // Nettoyer les cellules restantes dans openList et les cellules explorées
    while (!openList.empty()) {
        Cell* cell = openList.top();
        openList.pop();
        delete cell;
    }

    for (const auto& pair : closedList) {
        // Les cellules dans closedList ont déjà été supprimées
    }

    // Nettoyer la mémoire des cellules dans le chemin
    if (endCell != nullptr) {
        Cell* current = endCell;
        while (current != nullptr) {
            Cell* parent = current->parent;
            if (current != endCell) {
                delete current;
            }
            current = parent;
        }
    }

    return path;
}

sf::Vector2f SnakeAI::getNextDirection(const Snake& snake, const std::vector<Food>& foods) {
    // Initialiser la grille avec la position actuelle du serpent
    initializeGrid(snake, foods);

    // Obtenir la position de la tête du serpent
    sf::Vector2f headPosition = snake.getHeadPosition();
    int startX = static_cast<int>(headPosition.x / gridSize);
    int startY = static_cast<int>(headPosition.y / gridSize);

    // Trouver la nourriture la plus proche
    float minDistance = std::numeric_limits<float>::max();
    sf::Vector2f closestFoodPosition;
    for (const auto& food : foods) {
        float distance = std::sqrt(std::pow(food.getPosition().x - headPosition.x, 2) +
                                   std::pow(food.getPosition().y - headPosition.y, 2));
        if (distance < minDistance) {
            minDistance = distance;
            closestFoodPosition = food.getPosition();
        }
    }

    int endX = static_cast<int>(closestFoodPosition.x / gridSize);
    int endY = static_cast<int>(closestFoodPosition.y / gridSize);

    // Trouver le chemin du serpent vers la nourriture
    std::deque<sf::Vector2f> path = findPath(startX, startY, endX, endY);

    // Mettre à jour lastPath pour le dessin
    lastPath = path;

    // Vérifier si le chemin est sûr
    if (!isPathSafe(path, snake)) {
        // Si le chemin n'est pas sûr, essayer de suivre la queue
        sf::Vector2f tailPosition = snake.getTailPosition();
        int tailX = static_cast<int>(tailPosition.x / gridSize);
        int tailY = static_cast<int>(tailPosition.y / gridSize);

        std::deque<sf::Vector2f> tailPath = findPath(startX, startY, tailX, tailY);

        if (!tailPath.empty()) {
            // Mettre à jour lastPath pour le dessin
            lastPath = tailPath;

            // Suivre la queue
            sf::Vector2f nextPosition = tailPath[1];
            sf::Vector2f direction = nextPosition - headPosition;

            // Normaliser la direction au gridSize
            if (direction.x > 0) return sf::Vector2f(gridSize, 0.f);    // Droite
            if (direction.x < 0) return sf::Vector2f(-gridSize, 0.f);   // Gauche
            if (direction.y > 0) return sf::Vector2f(0.f, gridSize);    // Bas
            if (direction.y < 0) return sf::Vector2f(0.f, -gridSize);   // Haut
        } else {
            // Vider lastPath car aucun chemin n'a été trouvé
            lastPath.clear();
        }
    } else if (path.size() >= 2) {
        // Le chemin vers la nourriture est sûr
        sf::Vector2f nextPosition = path[1];
        sf::Vector2f direction = nextPosition - headPosition;

        // Normaliser la direction au gridSize
        if (direction.x > 0) return sf::Vector2f(gridSize, 0.f);    // Droite
        if (direction.x < 0) return sf::Vector2f(-gridSize, 0.f);   // Gauche
        if (direction.y > 0) return sf::Vector2f(0.f, gridSize);    // Bas
        if (direction.y < 0) return sf::Vector2f(0.f, -gridSize);   // Haut
    } else {
        // Vider lastPath car aucun chemin n'a été trouvé
        lastPath.clear();
    }

    // Si aucun chemin sûr n'est trouvé, essayer de se déplacer en toute sécurité
    // ...

    // Vider lastPath car aucun chemin n'a été trouvé
    lastPath.clear();

    // Si aucune direction sûre n'est trouvée, ne pas bouger
    return sf::Vector2f(0.f, 0.f);
}
