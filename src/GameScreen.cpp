#include "GameScreen.h"
#include <SFML/Graphics.hpp>
#include <iostream>

GameScreen::GameScreen(const std::string& name, float windowWidth, float windowHeight)
    : Scene(name),
      screenManager(SceneManager::getInstance()),
      windowWidth(windowWidth),
      windowHeight(windowHeight),
      gridSize(20.f),
      spawnInterval(5.f)
{
}

void GameScreen::init() {
    snake = Snake();

    spawnFood();

    std::cout << "GameScreen initialized.\n";
}

void GameScreen::handleInput(InputManager& inputManager) {
    snake.handleInput(keyboardManager, inputManager);
}

void GameScreen::update(float deltaTime) {
    snake.update(deltaTime);

    for (auto& food : foods) {
        food.update(deltaTime);
    }

    checkFoodCollision();

    checkSelfCollision();

    checkBoundaryCollision();

    if (spawnClock.getElapsedTime().asSeconds() >= spawnInterval) {
        spawnFood();
        spawnClock.restart();
    }
}

void GameScreen::draw(sf::RenderWindow& window) {
    window.draw(snake);
    for (const auto& food : foods) {
        window.draw(food);
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
        } else {
            ++it;
        }
    }
}

void GameScreen::checkSelfCollision() {
    if (snake.checkSelfCollision()) {
        std::cout << "Snake collided with itself! Game Over.\n";
        exit(1);
    }
}

void GameScreen::checkBoundaryCollision() {
    sf::Vector2f headPosition = snake.getHeadPosition();

    if (headPosition.x < 0.f || headPosition.x >= windowWidth ||
        headPosition.y < 0.f || headPosition.y >= windowHeight) {
        std::cout << "Snake collided with the boundary! Game Over.\n";
        exit(1);
    }
}

void GameScreen::spawnFood() {
    if (foods.size() < 1) {
        foods.emplace_back(windowWidth, windowHeight, gridSize);
    }
}
