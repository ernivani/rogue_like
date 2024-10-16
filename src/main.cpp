#include <SFML/Graphics.hpp>
#include <sstream>

int main()
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktop, "SFML works!", sf::Style::Fullscreen);
    window.setFramerateLimit(120);
    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color::Green);
    
    shape.setPosition((desktop.width - shape.getRadius() * 2) / 2, (desktop.height - shape.getRadius() * 2) / 2);

    float moveSpeed = 300.0f;
    sf::Clock clock;
    sf::Font font;
    if (!font.loadFromFile("res/fonts/cocogoose.ttf")) {
        return -1; // Handle error
    }
    sf::Text fpsText;
    fpsText.setFont(font);
    fpsText.setCharacterSize(24);
    fpsText.setFillColor(sf::Color::White);
    fpsText.setPosition(desktop.width - 100, 10);

    while (window.isOpen())
    {
        sf::Time deltaTime = clock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Vector2f movement(0.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            movement.x -= moveSpeed * deltaTime.asSeconds();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            movement.x += moveSpeed * deltaTime.asSeconds();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            movement.y -= moveSpeed * deltaTime.asSeconds();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            movement.y += moveSpeed * deltaTime.asSeconds();
        }
        shape.move(movement);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }

        // Calculate FPS
        float fps = 1.0f / deltaTime.asSeconds();
        std::stringstream ss;
        ss << "FPS: " << static_cast<int>(fps);
        fpsText.setString(ss.str());

        window.clear();
        window.draw(shape);
        window.draw(fpsText);
        window.display();
    }

    return 0;
}