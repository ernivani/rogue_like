// EditScene.h
#ifndef EDITSCENE_H
#define EDITSCENE_H

#include "Scene.h"
#include <vector>

class EditScene : public Scene {
public:
    void init() override;
    void handleInput(InputManager& inputManager) override;
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    void cleanup() override;

    void saveScene(const std::string& filename);

private:
    std::vector<sf::Drawable*> objects;
    // Additional members for editing
};

#endif // EDITSCENE_H
