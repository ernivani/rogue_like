#include "Snake.h"
#include <cmath>

Snake::Snake()
    : currentDirection(Direction::Right),
      nextDirection(Direction::Right),
      segmentSize(20.f),
      moveSpeed(0.f),
      moveTimer(0.f)
{
    for (int i = 0; i < 3; ++i) {
        sf::RectangleShape segment(sf::Vector2f(segmentSize - 1.f, segmentSize - 1.f));
        segment.setFillColor(sf::Color::Green);
        segment.setPosition(400.f - i * segmentSize, 300.f);
        segments.push_back(segment);
    }

}

void Snake::handleInput(const KeyboardManager& keyboardManager, const InputManager& inputManager) {
    if (keyboardManager.isActionDown("MoveUp", inputManager) && currentDirection != Direction::Down) {
        nextDirection = Direction::Up;
    }
    if (keyboardManager.isActionDown("MoveDown", inputManager) && currentDirection != Direction::Up) {
        nextDirection = Direction::Down;
    }
    if (keyboardManager.isActionDown("MoveLeft", inputManager) && currentDirection != Direction::Right) {
        nextDirection = Direction::Left;
    }
    if (keyboardManager.isActionDown("MoveRight", inputManager) && currentDirection != Direction::Left) {
        nextDirection = Direction::Right;
    }
}

void Snake::update(float deltaTime) {
    moveTimer += deltaTime;

    if (moveTimer >= moveSpeed) {
        moveTimer -= moveSpeed;

        currentDirection = nextDirection;

        sf::Vector2f movementOffset(0.f, 0.f);
        switch (currentDirection) {
            case Direction::Up:
                movementOffset.y -= segmentSize;
                break;
            case Direction::Down:
                movementOffset.y += segmentSize;
                break;
            case Direction::Left:
                movementOffset.x -= segmentSize;
                break;
            case Direction::Right:
                movementOffset.x += segmentSize;
                break;
        }

        sf::RectangleShape newHead = segments.front();
        newHead.move(movementOffset);
        segments.push_front(newHead);

        if (segments.size() > 0) {
            segments.pop_back();
        }
    }
}

void Snake::grow() {
    if (!segments.empty()) {
        sf::RectangleShape tail = segments.back();
        segments.push_back(tail);
    }
}

bool Snake::checkSelfCollision() const {
    if (segments.empty()) return false;

    sf::FloatRect headBounds = segments.front().getGlobalBounds();

    for (size_t i = 1; i < segments.size(); ++i) {
        if (segments[i].getGlobalBounds().intersects(headBounds)) {
            return true;
        }
    }

    return false;
}

sf::FloatRect Snake::getHeadBounds() const {
    if (segments.empty()) return sf::FloatRect();
    return segments.front().getGlobalBounds();
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto& segment : segments) {
        target.draw(segment, states);
    }
}

sf::Vector2f Snake::getHeadPosition() const {
    if (segments.empty()) return sf::Vector2f(0.f, 0.f);
    return segments.front().getPosition();
}

sf::Vector2f Snake::getTailPosition() const {
    if (segments.empty()) return sf::Vector2f(0.f, 0.f);
    return segments.back().getPosition();
}