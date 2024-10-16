// KeyboardManager.h
#ifndef KEYBOARDMANAGER_H
#define KEYBOARDMANAGER_H

#include <SFML/Window.hpp>
#include "InputManager.h"
#include <map>
#include <string>

class KeyboardManager {
public:
    KeyboardManager();

    void setKey(const std::string& action, sf::Keyboard::Key key);
    sf::Keyboard::Key getKey(const std::string& action) const;

    bool isActionPressed(const std::string& action, const InputManager& inputManager) const;
    bool isActionDown(const std::string& action, const InputManager& inputManager) const;
    bool isActionReleased(const std::string& action, const InputManager& inputManager) const;

private:
    std::map<std::string, sf::Keyboard::Key> m_keyBindings;
};

#endif // KEYBOARDMANAGER_H
