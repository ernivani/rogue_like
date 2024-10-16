// Window.cpp
#include "Window.h"

Window::Window(const std::string& title, const sf::Vector2u& size) {
    setup(title, size);
}

Window::~Window() {
    destroy();
}

void Window::setup(const std::string& title, const sf::Vector2u& size) {
    m_windowTitle = title;
    m_windowSize = size;
    m_isFullscreen = false;
    m_isDone = false;
    create();
}

void Window::create() {
    auto style = m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default;
    m_window.create({ m_windowSize.x, m_windowSize.y, 32 }, m_windowTitle, style);
}

void Window::destroy() {
    m_window.close();
}

void Window::beginDraw() {
    m_window.clear(sf::Color::Black);
}

void Window::endDraw() {
    m_window.display();
}

void Window::update() {
    // consume all the events so that make an issue
    // sf::Event event;
    // while (m_window.pollEvent(event)) {
    //     if (event.type == sf::Event::Closed) {
    //         m_isDone = true;
    //     }
    // }
}

bool Window::isOpen() const {
    return m_window.isOpen() && !m_isDone;
}

sf::RenderWindow* Window::getRenderWindow() {
    return &m_window;
}

sf::Vector2u Window::getWindowSize() const {
    return m_windowSize;
}

void Window::toggleFullscreen() {
    m_isFullscreen = !m_isFullscreen;
    destroy();
    create();
}

void Window::close() {
    m_isDone = true;
}

