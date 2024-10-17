#include "GameScreen.h"
#include <SFML/Graphics.hpp>
#include <iostream>

GameScreen::GameScreen(const std::string& name, float windowWidth, float windowHeight)
    : Scene(name),
      screenManager(SceneManager::getInstance()),
      windowWidth(windowWidth),
      windowHeight(windowHeight),
      gridSize(20.f),
      spawnInterval(5.f),
      ai(windowWidth, windowHeight, gridSize) // Initialisation de l'IA
{
}

void GameScreen::init() {
    snake = Snake();

    spawnFood();

    std::cout << "GameScreen initialized.\n";
}

void GameScreen::handleInput(InputManager& inputManager) {
    // Remplacer la gestion des entrées utilisateur par l'IA
    // L'IA déterminera la direction du serpent
}

void GameScreen::update(float deltaTime) {
    // Obtenir la direction de l'IA
    sf::Vector2f direction = ai.getNextDirection(snake, std::vector<Food>(foods.begin(), foods.end()));

    // Convertir la direction en Direction enum
    if (direction == sf::Vector2f(0.f, -gridSize)) {
        snake.setNextDirection(Direction::Up);
    }
    else if (direction == sf::Vector2f(0.f, gridSize)) {
        snake.setNextDirection(Direction::Down);
    }
    else if (direction == sf::Vector2f(-gridSize, 0.f)) {
        snake.setNextDirection(Direction::Left);
    }
    else if (direction == sf::Vector2f(gridSize, 0.f)) {
        snake.setNextDirection(Direction::Right);
    }

    // Mettre à jour le serpent
    snake.update(deltaTime);

    // Mettre à jour la nourriture
    for (auto& food : foods) {
        food.update(deltaTime);
    }

    // Vérifications de collision
    checkFoodCollision();
    checkSelfCollision();
    checkBoundaryCollision();

    // Gestion du spawn de nourriture
    if (spawnClock.getElapsedTime().asSeconds() >= spawnInterval) {
        spawnFood();
        spawnClock.restart();
    }

    // Récupérer le chemin actuel de l'IA
    currentPath = ai.getLastPath();
}


void GameScreen::draw(sf::RenderWindow& window) {
    window.draw(snake);
    for (const auto& food : foods) {
        window.draw(food);
    }

    // Dessiner le chemin de pathfinding
    if (currentPath.size() >= 2) {
        sf::VertexArray lines(sf::LinesStrip, currentPath.size());
        for (size_t i = 0; i < currentPath.size(); ++i) {
            lines[i].position = currentPath[i] + sf::Vector2f(gridSize / 2, gridSize / 2); // Centrer dans la cellule
            lines[i].color = sf::Color::Blue; // Couleur du chemin
        }
        window.draw(lines);
    }

    // Optionnel : Dessiner des cercles à chaque point du chemin pour une meilleure visualisation
    for (const auto& point : currentPath) {
        sf::CircleShape circle(gridSize / 4);
        circle.setFillColor(sf::Color::Blue);
        circle.setPosition(point + sf::Vector2f(gridSize / 2 - gridSize / 4, gridSize / 2 - gridSize / 4)); // Centrer
        window.draw(circle);
    }
}

void GameScreen::cleanup() {
    std::cout << "GameScreen cleaned up.\n";
}

void GameScreen::checkFoodCollision() {
    sf::FloatRect headBounds = snake.getHeadBounds();

    for (auto it = foods.begin(); it != foods.end(); ) {
        if (it->getBounds().intersects(headBounds)) {
            snake.grow();
            it->respawn();
            it = foods.erase(it);
            spawnFood();
        }
        else {
            ++it;
        }
    }
}

void GameScreen::checkSelfCollision() {
    if (snake.checkSelfCollision()) {
        std::cout << "Snake collided with itself! Game Over.\n";
        init();
    }
}

void GameScreen::checkBoundaryCollision() {
    sf::Vector2f headPosition = snake.getHeadPosition();

    if (headPosition.x < 0.f || headPosition.x >= windowWidth ||
        headPosition.y < 0.f || headPosition.y >= windowHeight) {
        std::cout << "Snake collided with the boundary! Game Over.\n";
        init();
    }
}

void GameScreen::spawnFood() {
    if (foods.size() < 1) {
        foods.emplace_back(windowWidth, windowHeight, gridSize);
    }
}
