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
    sf::Vector2f getTailPosition() const;

    void setMoveSpeed(float speed);

    std::deque<sf::Vector2f> getSegments() const {
        std::deque<sf::Vector2f> positions;
        for (const auto& segment : segments) {
            positions.push_back(segment.getPosition());
        }
        return positions;
    }

    int getLength() const {
        return segments.size();
    }

    float getMoveSpeed() const;


    // Ajoutez une méthode pour définir la prochaine direction
    void setNextDirection(Direction direction) {
        if ((direction == Direction::Up && currentDirection != Direction::Down) ||
            (direction == Direction::Down && currentDirection != Direction::Up) ||
            (direction == Direction::Left && currentDirection != Direction::Right) ||
            (direction == Direction::Right && currentDirection != Direction::Left)) {
            nextDirection = direction;
        }
    }

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
