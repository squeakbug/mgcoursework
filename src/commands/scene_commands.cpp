#include <memory>
#include <algorithm>

#include "commands/scene_commands.h"

#include "managers/drawmanager.h"
#include "managers/scenemanager.h"
#include "primitives/ipoly_transformable.h"
#include "primitives/iframe_transformable.h"
#include "primitives/iterrain_object.h"
#include "primitives/terrain_polygon_model.h"
#include "primitives/terrain_frame_model.h"
#include "lightmap/lightmap_pool.h"
#include "lightmap/lightmap_generator.h"


ConvertSceneObjectsToFrameCommand::ConvertSceneObjectsToFrameCommand()
{
    
}

void ConvertSceneObjectsToFrameCommand::execute()
{
    std::shared_ptr<SceneManager> scene_manager = SceneManager::instance();
    std::shared_ptr<Scene> scene = scene_manager->get_scene();

    for (auto &object : *scene)
    {
        // Обобщенный интерфейс здесь вызывает switch проблему (//TODO сделать необобщенный интерфейс)
        //if (std::dynamic_pointer_cast<IFrameTransformable<PolygonModel>>(object) != nullptr)
        //    object = std::dynamic_pointer_cast<IFrameTransformable<PolygonModel>>(object)->toFrameModel();

        //switch problem
        if (std::dynamic_pointer_cast<TerrainFrameModel>(object) != nullptr)
            object->enable();
        else if (std::dynamic_pointer_cast<TerrainPolygonModel>(object) != nullptr)
            object->disable();
    }
}

ConvertSceneObjectsToPolygonCommand::ConvertSceneObjectsToPolygonCommand()
{

}

void ConvertSceneObjectsToPolygonCommand::execute()
{
    std::shared_ptr<SceneManager> scene_manager = SceneManager::instance();
    std::shared_ptr<Scene> scene = scene_manager->get_scene();

    for (auto &object : *scene)
    {
        // Обобщенный интерфейс здесь вызывает switch проблему (//TODO сделать необобщенный интерфейс)
        //if (std::dynamic_pointer_cast<IPolyTransformable<FrameModel>>(object) != nullptr)
        //    object = std::dynamic_pointer_cast<IPolyTransformable<FrameModel>>(object)->toPolygonModel();

        //switch promblem
        if (std::dynamic_pointer_cast<TerrainPolygonModel>(object) != nullptr)
            object->enable();
        else if (std::dynamic_pointer_cast<TerrainFrameModel>(object) != nullptr)
            object->disable();
    }
}

UpdateTerrainObjectsCommand::UpdateTerrainObjectsCommand()
{

}

void UpdateTerrainObjectsCommand::execute()
{
    std::shared_ptr<SceneManager> scene_manager = SceneManager::instance();
    std::shared_ptr<Scene> scene = scene_manager->get_scene();

    for (auto &object : *scene)
    {
        if (std::dynamic_pointer_cast<ITerrainObject>(object) != nullptr)
            std::dynamic_pointer_cast<ITerrainObject>(object)->updateTerrainValues();
    }
}

GenerateLightmapsCommand::GenerateLightmapsCommand()
{
    
}

void GenerateLightmapsCommand::execute()
{
    std::shared_ptr<SceneManager> scene_manager = SceneManager::instance();
    std::shared_ptr<Scene> scene = scene_manager->get_scene();

    if (scene != nullptr)
    {
        std::shared_ptr<LightmapPool> pool = LightmapPool::instance();
        std::shared_ptr<LightmapGenerator> generator(new LightmapGenerator(pool));
        pool->clear();
        generator->visit(*scene);
        pool->resetCurPosition();
    }
}

RemoveTerrainCommand::RemoveTerrainCommand()
{

}

void RemoveTerrainCommand::execute()
{
    std::shared_ptr<Scene> scene = SceneManager::instance()->get_scene();

    if (scene != nullptr)
    {
        auto it = std::find_if(scene->begin(), scene->end(),
            [](std::shared_ptr<SceneObject> ptr)
            {
                return std::dynamic_pointer_cast<ITerrainObject>(ptr) != nullptr;
            }
        );

        while (it != scene->end())
        {
            scene->removeObject(it);

            it = std::find_if(scene->begin(), scene->end(),
                [](std::shared_ptr<SceneObject> ptr)
                {
                    return std::dynamic_pointer_cast<ITerrainObject>(ptr) != nullptr;
                }
            );
        }
    }
}

NextLightMapCommand::NextLightMapCommand()
{

}

void NextLightMapCommand::execute()
{
    std::shared_ptr<LightmapPool> pool = LightmapPool::instance();
    pool->incCurPosition();
}

RemoveTerrainLightmapCommand::RemoveTerrainLightmapCommand()
{

}

void RemoveTerrainLightmapCommand::execute()
{
    std::shared_ptr<Scene> scene = SceneManager::instance()->get_scene();
    std::shared_ptr<LightmapPool> pool = LightmapPool::instance();
    
    for (auto &obj : *scene)
    {
        if (std::dynamic_pointer_cast<TerrainPolygonModel>(obj) != nullptr)
            pool->eraseLightMap(obj->getId());
    }
}

SetupLightmapUsingCommand::SetupLightmapUsingCommand(bool isUsing)
    : _isUsing(isUsing)
{

}

void SetupLightmapUsingCommand::execute()
{
    std::shared_ptr<DrawManager> drawManager = DrawManager::instance();

    drawManager->setLightmapUsing(_isUsing);
}

SetShadowmapUsingCommand::SetShadowmapUsingCommand(bool isUsing)
    : _isUsing(isUsing)
{

}

void SetShadowmapUsingCommand::execute()
{
    std::shared_ptr<DrawManager> drawManager = DrawManager::instance();

    drawManager->setShadowmapUsing(_isUsing);
}
