#include "SceneManager.h"
#include <iostream>

void SceneManager::addScene(Scene* scene) {
    scenes.push_back(scene);
}

void SceneManager::changeScene(const std::string& name) {
    for (Scene* scene : scenes) {
        if (scene->getName() == name) {
            currentScene = scene;
            std::cout << "Changed to scene: " << name << std::endl;
            currentScene->init();
            return;
        }
    }
}

void SceneManager::deleteScene(const std::string& name) {
    for (auto it = scenes.begin(); it != scenes.end(); ++it) {
        if ((*it)->getName() == name) {
            (*it)->cleanup();
            delete *it;
            scenes.erase(it);
            return;
        }
    }
}

Scene* SceneManager::getCurrentScene() {
    return currentScene;
}
