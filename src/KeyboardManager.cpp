// KeyboardManager.cpp
#include "KeyboardManager.h"

KeyboardManager::KeyboardManager() {
    // Default key bindings
    m_keyBindings["MoveUp"] = sf::Keyboard::Z;
    m_keyBindings["MoveDown"] = sf::Keyboard::S;
    m_keyBindings["MoveLeft"] = sf::Keyboard::Q;
    m_keyBindings["MoveRight"] = sf::Keyboard::D;
    m_keyBindings["Action"] = sf::Keyboard::Space;
}

void KeyboardManager::setKey(const std::string& action, sf::Keyboard::Key key) {
    m_keyBindings[action] = key;
}

sf::Keyboard::Key KeyboardManager::getKey(const std::string& action) const {
    auto it = m_keyBindings.find(action);
    if (it != m_keyBindings.end()) {
        return it->second;
    }
    return sf::Keyboard::Unknown;
}

bool KeyboardManager::isActionPressed(const std::string& action, const InputManager& inputManager) const {
    sf::Keyboard::Key key = getKey(action);
    return inputManager.isKeyPressed(key);
}

bool KeyboardManager::isActionDown(const std::string& action, const InputManager& inputManager) const {
    sf::Keyboard::Key key = getKey(action);
    return inputManager.isKeyDown(key);
}

bool KeyboardManager::isActionReleased(const std::string& action, const InputManager& inputManager) const {
    sf::Keyboard::Key key = getKey(action);
    return inputManager.isKeyReleased(key);
}
