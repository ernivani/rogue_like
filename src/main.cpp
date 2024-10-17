#include "Window.h"
#include "Scene.h"
#include "MainScreen.h"
#include "GameScreen.h"
#include "SceneManager.h"
#include <iostream>
#include "InputManager.h"

int main() {
    Window window("Minimalist Roguelite Game", {800, 600}, 120,true);
    InputManager inputManager;

    SceneManager& sceneManager = SceneManager::getInstance();
    sceneManager.addScene(new MainScreen("MainScreen"));
    sceneManager.addScene(new GameScreen("GameScreen", window.getWindowSize().x, window.getWindowSize().y));
    sceneManager.changeScene("MainScreen");

    // Initial check for the current scene
    Scene* currentScene = sceneManager.getCurrentScene();

    if (currentScene == nullptr) {
        std::cerr << "No scene loaded!" << std::endl;
        return 1;
    }
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

        currentScene = sceneManager.getCurrentScene();

        if (currentScene) {
            currentScene->handleInput(inputManager);
            currentScene->update(deltaTime);

            window.beginDraw();
            currentScene->draw(*window.getRenderWindow());
            window.endDraw();
        }

        inputManager.update();
    }

    if (currentScene) {
        currentScene->cleanup();
        delete currentScene;
    }

    return 0;
}
