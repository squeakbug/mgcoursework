#include "managers/drawmanager.h"

DrawManager::DrawManager()
{

}


std::shared_ptr<DrawManager> DrawManager::instance()
{
    static std::shared_ptr<DrawManager> tmp(new DrawManager);

    return tmp;
}


void DrawManager::set_main_visitor(std::shared_ptr<DrawVisitor> visitor)
{
    _main_visitor = visitor;
}


void DrawManager::set_heightmap_visitor(std::shared_ptr<DrawVisitor> visitor)
{
    _heightmap_visitor = visitor;
}


void DrawManager::set_lightmap_visitor(std::shared_ptr<DrawVisitor> visitor)
{
    _lightmap_visitor = visitor;
}

std::shared_ptr<DrawVisitor> DrawManager::getMainVisitor()
{
    return _main_visitor;
}


void DrawManager::set_cam(std::shared_ptr<Camera> camera)
{
    _camera = camera;
}


std::shared_ptr<Camera> DrawManager::get_cam()
{
    return _camera;
}

void DrawManager::setLightmapUsing(bool state)
{
    _isLightmapUsing = state;
}

bool DrawManager::getLightmapUsing() const
{
    return _isLightmapUsing;
}


void DrawManager::setShadowmapUsing(bool state)
{
    _isShadowmapUsing = state;
}

bool DrawManager::getShadowmapUsing() const
{
    return _isShadowmapUsing;
}

void DrawManager::draw_scene(std::shared_ptr<Scene> scene)
{
    /* Если нет визитера, то выкинуть исключение */

    scene->accept(_main_visitor);
}


void DrawManager::draw_heightmap(std::shared_ptr<TerrainBlock> terrain)
{
    /* Если нет визитера, то выкинуть исключение */

    terrain->accept(*_heightmap_visitor);
}


void DrawManager::draw_lightmap(std::shared_ptr<LightmapPool> lightmap)
{

}

void DrawManager::setLightmapPool(std::shared_ptr<LightmapPool> pool)
{
    _lightmapPool = pool;
}

const std::shared_ptr<LightmapPool> DrawManager::getLightmapPool() const
{
    return _lightmapPool;
}

void DrawManager::setShadowmapPool(std::shared_ptr<ShadowmapPool> pool)
{
    _shadowmapPool = pool;
}

const std::shared_ptr<ShadowmapPool> DrawManager::getShadowmapPool() const
{
    return _shadowmapPool;
}
