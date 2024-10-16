// main.cpp
#include "Window.h"
#include "Scene.h"
#include "MainScreen.h"
#include "GameScreen.h"
#include <iostream>
#include "InputManager.h"

int main() {
    Window window("Minimalist Roguelite Game", {800, 600});
    InputManager inputManager;

    Scene* currentScene = new GameScreen();
    currentScene->init();

    sf::Clock clock;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        window.update(); // Handle window events

        // Handle input events
        sf::Event event;
        while (window.getRenderWindow()->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            inputManager.handleEvent(event);
        }

        currentScene->handleInput(inputManager);
        currentScene->update(deltaTime);

        window.beginDraw();
        currentScene->draw(*window.getRenderWindow());
        window.endDraw();

        inputManager.update(); // Reset per-frame input states

        // Scene transition logic
        // if (someCondition) {
        //     currentScene->cleanup();
        //     delete currentScene;
        //     currentScene = new GameScreen();
        //     currentScene->init();
        // }
    }

    currentScene->cleanup();
    delete currentScene;

    return 0;
}
