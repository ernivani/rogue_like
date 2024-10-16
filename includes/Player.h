// Player.h
#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "KeyboardManager.h"
#include "InputManager.h"
#include <cmath>

class Player : public sf::Drawable {
public:
    Player();

    void handleInput(const KeyboardManager& keyboardManager, const InputManager& inputManager);
    void update(float deltaTime);

private:
    sf::CircleShape shape;
    sf::Vector2f movement; // Store movement vector

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // PLAYER_H
