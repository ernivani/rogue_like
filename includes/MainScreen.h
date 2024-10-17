// MainScreen.h
#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include "Scene.h"
#include "SceneManager.h"

class MainScreen : public Scene {
public:
    MainScreen(const std::string& name) : Scene(name) {}
    void init() override;
    void handleInput(InputManager& inputManager) override;
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    void cleanup() override;

private:
    sf::Text titleText;
    sf::Font font;
    SceneManager& screenManager = SceneManager::getInstance();

};

#endif // MAINSCREEN_H
