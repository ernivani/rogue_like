#ifndef SNAKE_H
#define SNAKE_H

#include "Entity.h"
#include "KeyboardManager.h"
#include "InputManager.h"
#include <deque>
#include <SFML/Graphics.hpp>

enum class Direction {
    Up,
    Down,
    Left,
    Right
};

class Snake : public Entity {
public:
    Snake();

    void handleInput(const KeyboardManager& keyboardManager, const InputManager& inputManager);
    void update(float deltaTime) override;
    void grow();
    bool checkSelfCollision() const;
    sf::FloatRect getHeadBounds() const;
    sf::Vector2f getHeadPosition() const;

    void setMoveSpeed(float speed);
    float getMoveSpeed() const;

private:
    std::deque<sf::RectangleShape> segments;
    Direction currentDirection;
    Direction nextDirection;
    float segmentSize;

    float moveSpeed;
    float moveTimer;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // SNAKE_H
