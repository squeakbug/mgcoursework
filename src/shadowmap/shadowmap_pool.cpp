#include "shadowmap/shadowmap_pool.h"
#include "scene/scene.h"
#include "visitors/shadow_generator.h"
#include <iostream>


std::shared_ptr<ShadowmapPool> ShadowmapPool::instance()
{
    static std::shared_ptr<ShadowmapPool> tmp(new ShadowmapPool);

    return tmp;
}


void ShadowmapPool::addShadowmap(std::size_t sceneObjectId, std::shared_ptr<ZBuffer> shadowmap)
{
    //TODO проверить, что еще не добавлен

    _shadowmaps.insert(std::make_pair(sceneObjectId, shadowmap));
}

void ShadowmapPool::eraseShadowmap(std::size_t sceneObjectId)
{
    if (_shadowmaps.find(sceneObjectId) != _shadowmaps.end())
        _shadowmaps.erase(sceneObjectId);
}

bool ShadowmapPool::checkShadowmap(std::size_t sceneObjectId)
{
    return _shadowmaps.find(sceneObjectId) != _shadowmaps.end();
}

const std::shared_ptr<ZBuffer> ShadowmapPool::getShadowmap(std::size_t sceneObjectId) const
{
    //TODO проверка на существование

    return _shadowmaps.at(sceneObjectId);
}

void ShadowmapPool::clear()
{
    _shadowmaps.clear();
}

std::unordered_map<std::size_t, std::shared_ptr<ZBuffer>>::iterator ShadowmapPool::begin()
{
    return _shadowmaps.begin();
}

std::unordered_map<std::size_t, std::shared_ptr<ZBuffer>>::iterator ShadowmapPool::end()
{
    return _shadowmaps.end();
}

void ShadowmapPool::generateShadowmaps(Scene &scene)
{
    _shadowmaps.clear();

    for (auto &obj : scene)
    {
        if (obj->isEnabled() && std::dynamic_pointer_cast<DirectLightSource>(obj) != nullptr)
        {
            std::shared_ptr<DirectLightSource> lightSource = std::dynamic_pointer_cast<DirectLightSource>(obj);

            _generator->setCurrentLightSource(lightSource);
            _generator->visit(scene);
            addShadowmap(lightSource->getId(), _generator->getShadowmap());
        }
    }
}

void ShadowmapPool::setGenerator(std::shared_ptr<ShadowGenerator> generator)
{
    _generator = generator;
}
