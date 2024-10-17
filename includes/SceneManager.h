#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <memory>
#include <unordered_map>
#include <string>
#include "Scene.h"
#include <vector>

class SceneManager {
public:
    SceneManager() {
        currentScene;
    }

    static SceneManager& getInstance() {
        static SceneManager instance;
        return instance;
    }

    void addScene(Scene* scene);

    void changeScene(const std::string& name);

    void deleteScene(const std::string& name);

    Scene* getCurrentScene();

private:
    std::vector<Scene*> scenes;
    Scene* currentScene;
};

#endif // SCENEMANAGER_H