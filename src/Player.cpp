#include "Player.h"
#include <cmath>

Player::Player() {
    shape.setRadius(15.f);
    shape.setFillColor(sf::Color::Green);
    setPosition(400.f, 300.f);
    movement = sf::Vector2f(0.f, 0.f);
}

void Player::handleInput(const KeyboardManager& keyboardManager, const InputManager& inputManager) {
    float speed = 100.f;
    movement = sf::Vector2f(0.f, 0.f);

    if (keyboardManager.isActionDown("MoveUp", inputManager)) {
        movement.y -= speed;
    }
    if (keyboardManager.isActionDown("MoveDown", inputManager)) {
        movement.y += speed;
    }
    if (keyboardManager.isActionDown("MoveLeft", inputManager)) {
        movement.x -= speed;
    }
    if (keyboardManager.isActionDown("MoveRight", inputManager)) {
        movement.x += speed;
    }
}

void Player::update(float deltaTime) {
    if (movement.x != 0.f || movement.y != 0.f) {
        float length = std::sqrt(movement.x * movement.x + movement.y * movement.y);
        movement /= length;
    }

    move(movement * deltaTime * 100.f);
    shape.setPosition(getPosition());
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(shape, states);
}
