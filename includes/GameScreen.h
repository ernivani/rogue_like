// GameScreen.h
#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "Scene.h"
#include "Snake.h"
#include "Food.h"
#include "KeyboardManager.h"
#include "SceneManager.h"
#include <vector>

class GameScreen : public Scene {
public:
    GameScreen(const std::string& name, float windowWidth, float windowHeight);
    void init() override;
    void handleInput(InputManager& inputManager) override;
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    void cleanup() override;

private:
    Snake snake;
    std::vector<Food> foods;
    KeyboardManager keyboardManager;
    SceneManager& screenManager;
    float windowWidth;
    float windowHeight;
    float gridSize;
    sf::Clock spawnClock;
    float spawnInterval;

    void checkFoodCollision();
    void checkSelfCollision();
    void checkBoundaryCollision();
    void spawnFood();
};

#endif // GAMESCREEN_H
