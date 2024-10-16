// MainScreen.cpp
#include "MainScreen.h"

void MainScreen::init() {
    font.loadFromFile("res/fonts/cocogoose.ttf");
    titleText.setFont(font);
    titleText.setString("Main Screen");
    titleText.setCharacterSize(24);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(350.f, 280.f);
}

void MainScreen::handleInput(InputManager& inputManager) {
    if (inputManager.isKeyPressed(sf::Keyboard::Enter)) {
        // Transition to HomeScreen or GameScreen
    }
}

void MainScreen::update(float deltaTime) {
    // Update logic
}

void MainScreen::draw(sf::RenderWindow& window) {
    window.draw(titleText);
}

void MainScreen::cleanup() {
    // Cleanup resources
}
