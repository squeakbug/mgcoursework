#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <memory>

#include "managers/basemanager.h"
#include "scene/scene.h"

class SceneManager : public BaseManager
{
public:
    static std::shared_ptr<SceneManager> instance();

    void set_scene(std::shared_ptr<Scene> scene);
    std::shared_ptr<Scene> get_scene();

private:
    SceneManager();
    SceneManager(const SceneManager &other) = delete;
    SceneManager &operator=(const SceneManager &other) = delete;

private:
    std::shared_ptr<Scene> _scene;
};

#endif // SCENEMANAGER_H
