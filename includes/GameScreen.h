// GameScreen.h
#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "Scene.h"
#include "Player.h"
#include "KeyboardManager.h"
#include "SceneManager.h"

class GameScreen : public Scene {
public:

    GameScreen(const std::string& name) : Scene(name) {}
    void init() override;
    void handleInput(InputManager& inputManager) override;
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    void cleanup() override;

private:
    Player player;
    KeyboardManager keyboardManager;
    SceneManager& screenManager = SceneManager::getInstance();
};

#endif // GAMESCREEN_H
