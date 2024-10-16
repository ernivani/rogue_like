// MainScreen.h
#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include "Scene.h"

class MainScreen : public Scene {
public:
    void init() override;
    void handleInput(InputManager& inputManager) override;
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    void cleanup() override;

private:
    sf::Text titleText;
    sf::Font font;
};

#endif // MAINSCREEN_H
