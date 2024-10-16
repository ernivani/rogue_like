// Scene.h
#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics.hpp>
#include "InputManager.h"

class Scene {
public:
    virtual ~Scene() {}

    virtual void init() = 0;
    virtual void handleInput(InputManager& inputManager) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void cleanup() = 0;
};

#endif // SCENE_H
