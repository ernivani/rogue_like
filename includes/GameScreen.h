#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "Scene.h"
#include "Snake.h"
#include "Food.h"
#include "SnakeAI.h"
#include "SceneManager.h"
#include <deque>

class GameScreen : public Scene {
public:
    GameScreen(const std::string& name, float windowWidth, float windowHeight);
    virtual void init() override;
    virtual void handleInput(InputManager& inputManager) override;
    virtual void update(float deltaTime) override;
    virtual void draw(sf::RenderWindow& window) override;
    virtual void cleanup() override;

private:
    SceneManager& screenManager;
    float windowWidth;
    float windowHeight;
    float gridSize;
    float spawnInterval;
    Snake snake;
    std::vector<Food> foods;
    sf::Clock spawnClock;
    SnakeAI ai; // Instance de l'IA
    std::deque<sf::Vector2f> currentPath;

    void checkFoodCollision();
    void checkSelfCollision();
    void checkBoundaryCollision();
    void spawnFood();
};

#endif // GAMESCREEN_H
