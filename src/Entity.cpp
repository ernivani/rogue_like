#include "Entity.h"

Entity::Entity() : position(0.f, 0.f), movement(0.f, 0.f) {}

void Entity::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
}

sf::Vector2f Entity::getPosition() const {
    return position;
}

void Entity::move(const sf::Vector2f& offset) {
    position += offset;
}
