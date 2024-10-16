// HomeScreen.h
#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include "Scene.h"

class HomeScreen : public Scene {
public:
    void init() override;
    void handleInput(InputManager& inputManager) override;
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    void cleanup() override;

private:
    // Add members specific to HomeScreen
};

#endif // HOMESCREEN_H
