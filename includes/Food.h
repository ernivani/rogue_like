#ifndef FOOD_H
#define FOOD_H

#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <random>

class Food : public Entity {
public:
    Food(float windowWidth, float windowHeight, float gridSize);

    void update(float deltaTime) override;
    void respawn();
    sf::FloatRect getBounds() const;

private:
    sf::CircleShape shape;
    float windowWidth;
    float windowHeight;
    float gridSize;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // FOOD_H
