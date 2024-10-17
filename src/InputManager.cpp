// InputManager.cpp
#include "InputManager.h"
#include <iostream>

InputManager::InputManager() {}

void InputManager::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        m_keyDown[event.key.code] = true;
        m_keyPressed[event.key.code] = true;
    } else if (event.type == sf::Event::KeyReleased) {
        m_keyDown[event.key.code] = false;
        m_keyReleased[event.key.code] = true;
    }
}

bool InputManager::isKeyPressed(sf::Keyboard::Key key) const {
    auto it = m_keyPressed.find(key);
    return it != m_keyPressed.end() && it->second;
}

bool InputManager::isKeyDown(sf::Keyboard::Key key) const {
    auto it = m_keyDown.find(key);
    return it != m_keyDown.end() && it->second;
}

bool InputManager::isKeyReleased(sf::Keyboard::Key key) const {
    auto it = m_keyReleased.find(key);
    return it != m_keyReleased.end() && it->second;
}

void InputManager::update() {
    // Reset per-frame states
    m_keyPressed.clear();
    m_keyReleased.clear();
}
