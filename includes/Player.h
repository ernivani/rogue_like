#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "KeyboardManager.h"
#include "InputManager.h"

class Player : public Entity {
public:
    Player();

    void handleInput(const KeyboardManager& keyboardManager, const InputManager& inputManager);
    void update(float deltaTime) override;

private:
    sf::CircleShape shape;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // PLAYER_H
