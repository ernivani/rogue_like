// GameScreen.cpp
#include "GameScreen.h"

void GameScreen::init() {
    // Initialize game objects
}

void GameScreen::handleInput(InputManager& inputManager) {
    player.handleInput(keyboardManager, inputManager);
    // Handle other inputs
}

void GameScreen::update(float deltaTime) {
    player.update(deltaTime);
    // Update other game objects
}

void GameScreen::draw(sf::RenderWindow& window) {
    window.draw(player);
    // Draw other game objects
}

void GameScreen::cleanup() {
    // Cleanup resources
}
