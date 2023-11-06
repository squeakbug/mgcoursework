#include "lightmap/lightmap_pool.h"

std::shared_ptr<LightmapPool> LightmapPool::instance()
{
    static std::shared_ptr<LightmapPool> tmp(new LightmapPool);

    return tmp;
}

void LightmapPool::addLightMap(std::size_t sceneId, std::shared_ptr<FrameBuffer> lightmap)
{
    //TODO проверить, что еще не добавлен

    _lightmaps.insert(std::make_pair(sceneId, lightmap));
}

void LightmapPool::eraseLightMap(std::size_t sceneId)
{
    if (_lightmaps.find(sceneId) != _lightmaps.end())
        _lightmaps.erase(sceneId);
    
    //TODO Generate exception
}

bool LightmapPool::checkLightmap(std::size_t sceneObjectId)
{
    return _lightmaps.find(sceneObjectId) != _lightmaps.end();
}

const std::shared_ptr<FrameBuffer> LightmapPool::getLightmap(std::size_t sceneObjectId) const
{
    //TODO проверка на существование

    return _lightmaps.at(sceneObjectId);
}

void LightmapPool::clear()
{
    _lightmaps.clear();
    _curPosition = _lightmaps.begin();
}

std::unordered_map<std::size_t, std::shared_ptr<FrameBuffer>>::iterator LightmapPool::begin()
{
    return _lightmaps.begin();
}

std::unordered_map<std::size_t, std::shared_ptr<FrameBuffer>>::iterator LightmapPool::end()
{
    return _lightmaps.end();
}

std::unordered_map<std::size_t, std::shared_ptr<FrameBuffer>> ::iterator LightmapPool::getCurPosition()
{
    return _curPosition;
}

void LightmapPool::resetCurPosition()
{
    _curPosition = _lightmaps.begin();
}

void LightmapPool::incCurPosition()
{
    if (std::next(_curPosition) != _lightmaps.end())
        _curPosition++;
    else
        _curPosition = _lightmaps.begin();
}

void LightmapPool::accept(Visitor &visitor)
{
    visitor.visit(*this);
}
