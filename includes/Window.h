// Window.h
#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include <string>

class Window {
public:
    Window(const std::string& title, const sf::Vector2u& size, int frameRateLimit = 60, bool isFullscreen = false);
    ~Window();

    void beginDraw(); // Clear the window
    void endDraw();   // Display the window

    void update();    // Handle events

    bool isOpen() const;
    sf::RenderWindow* getRenderWindow();

    sf::Vector2u getWindowSize() const;

    void toggleFullscreen();
    void close();

private:
    void setup(const std::string& title, const sf::Vector2u& size);
    void destroy();
    void create();

    sf::RenderWindow m_window;
    sf::Vector2u m_windowSize;
    std::string m_windowTitle;

    bool m_isDone;
    bool m_isFullscreen;
};

#endif // WINDOW_H
