#include <memory>

#include "commands/light_sources_commands.h"

#include "scene/scene.h"
#include "scene/scene_selector.h"
#include "managers/scenemanager.h"
#include "primitives/light_types/direct_light_source.h"
#include "primitives/polygonmodel.h"
#include "shaders/fragment_shader.h"
#include "managers/drawmanager.h"

const vec3<> defaultColor = { 0.f, 0.f, 0.f };

AddNewLightSourceCommand::AddNewLightSourceCommand(vec3<> color, float ambient, float diffuse, float specular, bool state)
    : _color(color),
    _ambient(ambient),
    _diffuse(diffuse),
    _specular(specular),
    _state(state)
{

}

AddNewDirectLightSourceCommand::AddNewDirectLightSourceCommand(vec3<> color, float ambient, float diffuse, float specular, bool state, vec3<> direction)
    : AddNewLightSourceCommand(color, ambient, diffuse, specular, state),
    _direction(direction)
{

}

void AddNewDirectLightSourceCommand::execute()
{
    std::shared_ptr<Scene> scene = SceneManager::instance()->get_scene();
    auto lightSource = std::shared_ptr<SceneObject>(new DirectLightSource(_ambient, _diffuse, _specular, _color, _state, _direction));

    scene->add_obj(lightSource);
}

EditLightSourceCommand::EditLightSourceCommand(vec3<> newColor,
    float newAmbient, float newDiffuse, float newSpecular, size_t indx)
    : _color(newColor),
    _ambient(newAmbient),
    _diffuse(newDiffuse),
    _specular(newSpecular),
    _indx(indx)
{

}

EditLightSourceColorCommand::EditLightSourceColorCommand(vec3<> newColor, size_t indx)
    : _color(newColor),
    _indx(indx)
{

}

void EditLightSourceColorCommand::execute()
{
    std::shared_ptr<Scene> scene = SceneManager::instance()->get_scene();

    std::shared_ptr<LightSource> searchResult = nullptr;
    size_t i = 0;
    for (auto &obj : *scene)
    {
        if (std::dynamic_pointer_cast<LightSource>(obj) != nullptr)
        {
            if (i == _indx)
            {
                searchResult = std::dynamic_pointer_cast<LightSource>(obj);
                break;
            }
            i++;
        }
    }

    if (searchResult == nullptr)
    {
        /* throw Exception */   // TODO source with certain indx must be in the list
    }

    std::shared_ptr<DirectLightSource> editTarget = std::dynamic_pointer_cast<DirectLightSource>(searchResult);
    if (editTarget == nullptr)
    {
        /* throw Exception */   // TODO source must be instance of direct source
    }

    editTarget->setColor(_color);
}

EditDirectLightSourceCommand::EditDirectLightSourceCommand(
    float newAmbient, float newDiffuse, float newSpecular,
    size_t indx, vec3<> newDirection)
    : EditLightSourceCommand(defaultColor, newAmbient, newDiffuse, newSpecular, indx),
    _direction(newDirection)
{
    _isColorEdit = false;
}

EditDirectLightSourceCommand::EditDirectLightSourceCommand(vec3<> newColor,
    float newAmbient, float newDiffuse, float newSpecular,
    size_t indx, vec3<> newDirection)
    : EditLightSourceCommand(newColor, newAmbient, newDiffuse, newSpecular, indx),
    _direction(newDirection)
{
    _isColorEdit = true;
}

void EditDirectLightSourceCommand::execute()
{
    std::shared_ptr<Scene> scene = SceneManager::instance()->get_scene();

    std::shared_ptr<LightSource> searchResult = nullptr;
    size_t i = 0;
    for (auto &obj : *scene)
    {
        if (std::dynamic_pointer_cast<LightSource>(obj) != nullptr)
        {
            if (i == _indx)
            {
                searchResult = std::dynamic_pointer_cast<LightSource>(obj);
                break;
            }
            i++;
        }
    }

    if (searchResult == nullptr)
    {
        /* throw Exception */   // TODO source with certain indx must be in the list
    }

    std::shared_ptr<DirectLightSource> editTarget = std::dynamic_pointer_cast<DirectLightSource>(searchResult);
    if (editTarget == nullptr)
    {
        /* throw Exception */   // TODO source must be instance of direct source
    }

    if (_isColorEdit)
        editTarget->setColor(_color);
    editTarget->setAmbient(_ambient);
    editTarget->setDiffuse(_diffuse);
    editTarget->setSpecular(_specular);
    editTarget->setDirection(_direction);
}

RemoveLightSourceCommand::RemoveLightSourceCommand(size_t indx)
    : _indx(indx)
{

}

void RemoveLightSourceCommand::execute()
{
    std::shared_ptr<Scene> scene = SceneManager::instance()->get_scene();

    size_t i = 0;
    auto it = scene->begin();
    for (auto &obj : *scene)
    {
        if (std::dynamic_pointer_cast<LightSource>(obj) != nullptr)
        {
            if (i == _indx)
            {
                scene->removeObject(it);
                return ;
            }
            i++;
        }
        it++;
    }

    /* throw Exception */   // TODO source with certain indx must be in the list
}

EnableLightSourceCommand::EnableLightSourceCommand(size_t indx)
    : _indx(indx)
{

}

void EnableLightSourceCommand::execute()
{
    std::shared_ptr<Scene> scene = SceneManager::instance()->get_scene();

    size_t i = 0;
    for (auto &obj : *scene)
    {
        if (std::dynamic_pointer_cast<LightSource>(obj) != nullptr)
        {
            if (i == _indx)
            {
                std::dynamic_pointer_cast<LightSource>(obj)->enable();
                return ;
            }
            i++;
        }
    }
}

DisableLightSourceCommand::DisableLightSourceCommand(size_t indx)
    : _indx(indx)
{

}

void DisableLightSourceCommand::execute()
{
    std::shared_ptr<Scene> scene = SceneManager::instance()->get_scene();

    size_t i = 0;
    for (auto &obj : *scene)
    {
        if (std::dynamic_pointer_cast<LightSource>(obj) != nullptr)
        {
            if (i == _indx)
            {
                std::dynamic_pointer_cast<LightSource>(obj)->disable();
                return ;
            }
            i++;
        }
    }
}

SelectLightSourceDataCommand::SelectLightSourceDataCommand(size_t indx, vec3<> &color, float &ambient, float &diffuse, float &specular)
    : _indx(indx),
    _color(color),
    _ambient(ambient),
    _diffuse(diffuse),
    _specular(specular)
{

}

SelectDirectLightSourceDataCommand::SelectDirectLightSourceDataCommand(size_t indx, vec3<> &color,
    float &ambient, float &diffuse, float &specular, vec3<> &direction)
    : SelectLightSourceDataCommand(indx, color, ambient, diffuse, specular),
    _direction(direction)
{

}

void SelectDirectLightSourceDataCommand::execute()
{
    std::shared_ptr<Scene> scene = SceneManager::instance()->get_scene();

    std::shared_ptr<LightSource> searchResult = nullptr;
    size_t i = 0;
    for (auto &obj : *scene)
    {
        if (std::dynamic_pointer_cast<LightSource>(obj) != nullptr)
        {
            if (i == _indx)
            {
                searchResult = std::dynamic_pointer_cast<LightSource>(obj);
                break;
            }
            i++;
        }
    }

    if (searchResult == nullptr)
    {
        /* throw Exception */   // TODO source with certain indx must be in the list
    }

    std::shared_ptr<DirectLightSource> editTarget = std::dynamic_pointer_cast<DirectLightSource>(searchResult);
    if (editTarget == nullptr)
    {
        /* throw Exception */   // TODO source must be direct source
    }

    _ambient = editTarget->getAmbient();
    _diffuse = editTarget->getDiffuse();
    _specular = editTarget->getSpecular();
    _direction = editTarget->getDirection();
    _color = editTarget->getColor();
}

UpdateFragmentShadersLightMapSourcesCommand::UpdateFragmentShadersLightMapSourcesCommand()
{

}

void UpdateFragmentShadersLightMapSourcesCommand::execute()
{
    std::shared_ptr<Scene> scene = SceneManager::instance()->get_scene();

    if (scene != nullptr)
    {
        for (auto &object : *scene)
        {
            if (std::dynamic_pointer_cast<PolygonModel>(object) != nullptr)
            {
                std::shared_ptr<FragmentShader> fragmentShader = std::dynamic_pointer_cast<PolygonModel>(object)->getFragmentShader();
                fragmentShader->setDirectSources(SceneSelector::selectEnabledDirectLightSources(scene));
                //TODO setting up other local light sources
            }
        }
    }
}

UpdateShadowmapPoolCommand::UpdateShadowmapPoolCommand()
{

}

void UpdateShadowmapPoolCommand::execute()
{
    std::shared_ptr<DrawManager> drawManager = DrawManager::instance();

    auto shadowmapPool = drawManager->getShadowmapPool();
    std::shared_ptr<Scene> scene = SceneManager::instance()->get_scene();
    shadowmapPool->generateShadowmaps(*scene);
}
