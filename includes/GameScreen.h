// GameScreen.h
#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "Scene.h"
#include "Player.h"
#include "KeyboardManager.h"

class GameScreen : public Scene {
public:
    void init() override;
    void handleInput(InputManager& inputManager) override;
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    void cleanup() override;

private:
    Player player;
    KeyboardManager keyboardManager;
    // Other game objects
};

#endif // GAMESCREEN_H
