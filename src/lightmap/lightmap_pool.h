#ifndef LIGHTMAP_POOL_H
#define LIGHTMAP_POOL_H

#include <unordered_map>
#include <cstddef>
#include <memory>

//TODO Заменить тип FrameBuffer на тип Texture
#include "frame_buffers/frame_buffer.h"
#include "visitors/visitor.h"

class LightmapPool
{
public:
    static std::shared_ptr<LightmapPool> instance();

    void addLightMap(std::size_t sceneObjectId, std::shared_ptr<FrameBuffer> lightmap);
    void eraseLightMap(std::size_t sceneObjectId);
    bool checkLightmap(std::size_t sceneObjectId);
    const std::shared_ptr<FrameBuffer> getLightmap(std::size_t sceneObjectId) const;
    void clear();

    std::unordered_map<std::size_t, std::shared_ptr<FrameBuffer>>::iterator begin();
    std::unordered_map<std::size_t, std::shared_ptr<FrameBuffer>>::iterator end();

    /* Данный класс несоответствует первому принципу SOLID */

    void accept(Visitor &Visitor);

    std::unordered_map<std::size_t, std::shared_ptr<FrameBuffer>> ::iterator getCurPosition();
    void resetCurPosition();
    void incCurPosition();

private:
    LightmapPool() = default;
    LightmapPool(const LightmapPool &other) = delete;

private:
    std::unordered_map<std::size_t, std::shared_ptr<FrameBuffer>> _lightmaps;
    std::unordered_map<std::size_t, std::shared_ptr<FrameBuffer>> ::iterator _curPosition;
};

#endif