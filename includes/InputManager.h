// InputManager.h
#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SFML/Window.hpp>
#include <map>

class InputManager {
public:
    InputManager();

    void handleEvent(const sf::Event& event);

    bool isKeyPressed(sf::Keyboard::Key key) const;
    bool isKeyDown(sf::Keyboard::Key key) const;
    bool isKeyReleased(sf::Keyboard::Key key) const;

    void update(); // Reset per-frame input states

private:
    std::map<sf::Keyboard::Key, bool> m_keyDown;
    std::map<sf::Keyboard::Key, bool> m_keyPressed;
    std::map<sf::Keyboard::Key, bool> m_keyReleased;
};

#endif // INPUTMANAGER_H
