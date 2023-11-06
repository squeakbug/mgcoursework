#include "managers/scenemanager.h"

SceneManager::SceneManager()
    : _scene(new Scene)
{

}



std::shared_ptr<SceneManager> SceneManager::instance()
{
    static std::shared_ptr<SceneManager> tmp(new SceneManager);

    return tmp;
}


void SceneManager::set_scene(std::shared_ptr<Scene> scene)
{
    _scene = scene;
}


std::shared_ptr<Scene> SceneManager::get_scene()
{
    return _scene;
}
