#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable {
public:
    Entity();
    
    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;
    void move(const sf::Vector2f& offset);
    
    virtual void update(float deltaTime) = 0; // Pure virtual function to ensure subclasses implement their own update logic
    
protected:
    sf::Vector2f position; // Store entity position
    sf::Vector2f movement; // Store movement vector

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0; // Pure virtual for custom drawing in derived classes
};

#endif // ENTITY_H
